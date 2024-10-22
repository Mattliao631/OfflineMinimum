### Problem1 of Chapter19 Disjoint sets data structure of Introduction to Algorithms 4th edition

Implementing a heap to run online minimum as the ground truth for verification
(Since the worst case is n Insert and then arbitrary amount of Extract, the complexity is O(mlgn) where m is the number of extraction)

Using disjoint set to implement offline minimum by implementing disjoint set for each string separated by the extract operation and set original reference for each number to the proper set number.

And then from small number to large number determine the proper set number(extraction number) and output it to the corresponding answer index, and then combine the current set and the next set(since the extraction is performed, the next extraction should find min from the previous one's.

A little change need to be done to disjoint set implementation to ensure union by rank won't break the current-next relation of sets(if current is set to parent, the set number should be change, the reference of set number to two original root should be change as well.)

By implementing such algorithm we can utilize the nearly linear time complexity of disjoint sets with union by rank and path compression to perform offline minimum which can run in O((m+1)a'(m)) where a'(n) = min{k: Ak(1)>=lg(n+1)}, Ak is the Ackerman function of the Textbook's version, the complexity can be reduced to O(ma'(m)).
