add_executable(matrixGraph 01_MatrixGraph/main.c
        01_MatrixGraph/matrixGraph.c
        01_MatrixGraph/matrixGraph.h)
add_executable(listGraph 02_ListGraph/main.c
        02_ListGraph/listGraph.c
        02_ListGraph/listGraph.h)
add_executable(crossLinkGraph 03_CrossLinkGraph/main.c
        03_CrossLinkGraph/crossLinkGraph.c
        03_CrossLinkGraph/crossLinkGraph.h)
add_executable(multiListGraph 04_MultiListGraph/main.c
        04_MultiListGraph/multiListGraph.c
        04_MultiListGraph/multiListGraph.h)
add_executable(KruskalAlgorithmTree 05_MinimumSpanningTree/main1.c
        05_MinimumSpanningTree/Kruskal.c
        05_MinimumSpanningTree/Kruskal.h
        01_MatrixGraph/matrixGraph.c
        01_MatrixGraph/matrixGraph.h
        05_MinimumSpanningTree/common.h)
add_executable(PrimAlgorithmTree 05_MinimumSpanningTree/main2.c
        05_MinimumSpanningTree/Prim.c
        05_MinimumSpanningTree/Prim.h
        01_MatrixGraph/matrixGraph.c
        01_MatrixGraph/matrixGraph.h
        05_MinimumSpanningTree/common.h)