#include "graph.h"
#include <unistd.h>

template<
typename file_vert_t, typename file_index_t, typename file_weight_t,
typename new_vert_t, typename new_index_t, typename new_weight_t>
graph<file_vert_t,file_index_t, file_weight_t,
new_vert_t,new_index_t,new_weight_t>
::graph(
		const char *beg_file,
		const char *csr_file,
		const char *weight_file)
{
	double tm=wtime();
	FILE *file=NULL;
	file_index_t ret;
	
	vert_count=fsize(beg_file)/sizeof(file_index_t) - 1;
	edge_count=fsize(csr_file)/sizeof(file_vert_t);
	
	file=fopen(beg_file, "rb");
	if(file!=NULL)
	{
		file_index_t *tmp_beg_pos=NULL;

		if(posix_memalign((void **)&tmp_beg_pos, getpagesize(),
					sizeof(file_index_t)*(vert_count+1)))
			perror("posix_memalign");

		ret=fread(tmp_beg_pos, sizeof(file_index_t), 
				vert_count+1, file);
		assert(ret==vert_count+1);
		fclose(file);
		edge_count=tmp_beg_pos[vert_count];
		std::cout<<"Expected edge count: "<<tmp_beg_pos[vert_count]<<"\n";

        assert(tmp_beg_pos[vert_count]>0);

		//converting to new type when different 
		if(sizeof(file_index_t)!=sizeof(new_index_t))
		{
			if(posix_memalign((void **)&beg_pos, getpagesize(),
					sizeof(new_index_t)*(vert_count+1)))
			perror("posix_memalign");
			for(new_index_t i=0;i<vert_count+1;++i)
				beg_pos[i]=(new_index_t)tmp_beg_pos[i];
			delete[] tmp_beg_pos;
		}else{beg_pos=(new_index_t*)tmp_beg_pos;}
	}else std::cout<<"beg file cannot open\n";

	file=fopen(csr_file, "rb");
	if(file!=NULL)
	{
		file_vert_t *tmp_csr = NULL;
		if(posix_memalign((void **)&tmp_csr,getpagesize(),
						sizeof(file_vert_t)*edge_count))
			perror("posix_memalign");
		
		ret=fread(tmp_csr, sizeof(file_vert_t), edge_count, file);
        std::cout<<ret<<" "<<edge_count<<"\n";
		assert(ret==edge_count);
		assert(ret==beg_pos[vert_count]);
		fclose(file);
			
		if(sizeof(file_vert_t)!=sizeof(new_vert_t))
		{
			if(posix_memalign((void **)&csr,getpagesize(),
						sizeof(new_vert_t)*edge_count))
				perror("posix_memalign");
			for(new_index_t i=0;i<edge_count;++i)
				csr[i]=(new_vert_t)tmp_csr[i];
			delete[] tmp_csr;
		}else csr=(new_vert_t*)tmp_csr;

	}else std::cout<<"CSR file cannot open\n";


	file=fopen(weight_file, "rb");
	if(file!=NULL)
	{
		file_weight_t *tmp_weight = NULL;
		if(posix_memalign((void **)&tmp_weight,getpagesize(),
					sizeof(file_weight_t)*edge_count))
			perror("posix_memalign");
		
		ret=fread(tmp_weight, sizeof(file_weight_t), edge_count, file);
		assert(ret==edge_count);
		fclose(file);
	
		if(sizeof(file_weight_t)!=sizeof(new_weight_t))
		{
			if(posix_memalign((void **)&weight,getpagesize(),
						sizeof(new_weight_t)*edge_count))
				perror("posix_memalign");
			for(new_index_t i=0;i<edge_count;++i)
				weight[i]=(new_weight_t)tmp_weight[i];
			delete[] tmp_weight;
		}else weight=(new_weight_t*)tmp_weight;
	}
	else std::cout<<"Weight file cannot open\n";

	std::cout<<"Graph load (success): "<<vert_count<<" verts, "
		<<edge_count<<" edges "<<wtime()-tm<<" second(s)\n";
}

template<
typename file_vert_t, typename file_index_t, typename file_weight_t,
typename new_vert_t, typename new_index_t, typename new_weight_t>
void graph<file_vert_t, file_index_t, file_weight_t, new_vert_t, new_index_t, new_weight_t>::BFS(new_vert_t source)
{
    // Array to keep track of visited vertices
    bool *visited = new bool[vert_count];
    for(new_index_t i = 0; i < vert_count; i++)
        visited[i] = false;

    // Queue for BFS
    std::queue<new_vert_t> queue;

    // Visit the source node
    visited[source] = true;
    queue.push(source);

    while(!queue.empty())
    {
        // Dequeue a vertex from the queue
        new_vert_t u = queue.front();
        queue.pop();
        std::cout << u << " ";

        // Get all adjacent vertices of the dequeued vertex u
        // If an adjacent vertex has not been visited, then mark it visited and enqueue it
        for(new_index_t i = beg_pos[u]; i < beg_pos[u+1]; i++)
        {
            new_vert_t v = csr[i];
            if(!visited[v])
            {
                visited[v] = true;
                queue.push(v);
            }
        }
    }

    delete[] visited;
}

void graph<file_vert_t, file_index_t, file_weight_t, new_vert_t, new_index_t, new_weight_t>::printBFSPath()
{
    // Check if BFS path is empty
    if(bfsPath.empty())
    {
        std::cout << "BFS traversal path is empty!" << std::endl;
        return;
    }

    // Print BFS traversal path
    for(new_index_t i = 0; i < bfsPath.size(); i++)
    {
        std::cout << bfsPath[i];
        if(i < bfsPath.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
}

