//are we handling the case where T is greater than N?
#include <stdio.h>

int main(void) {
    FILE *input = fopen("artemis.in", "r");
    if (input == NULL) return 1;

    int nTrees, minTrees; 
    if (fscanf(input, "%d%d", &nTrees, &minTrees) != 2) return 1; //If fewer than two integers were read, the program exits with a failure status.
    static int x[20000], y[20000];  //x[0] and y[0] hold the coordinates of tree 1, and x[1] and y[1] hold tree 2. Store tree i + 1 at x[i] and y[i]

    for (int i = 0; i < nTrees; ++i) { //Each iteration handles one tree.
        if (fscanf(input, "%d%d", &x[i], &y[i]) != 2) return 1; //The fscanf call reads and stores one tree’s coordinates.
        
    }
    fclose(input); //By this point, the loop has copied every tree’s coordinates into x and y. fclose(input) releases the file handle because the program has finished reading. The coordinates stay in the arrays for the rectangle search.
    
    int bestCount = nTrees + 1; //If there are 8 trees, bestCount starts at 9. Even a valid rectangle containing all 8 trees can become the first answer because 8 < 9. If we started at 8, the check 8 < 8 would skip it.
    int bestI = -1, bestJ = -1; // bestI and bestJ record which two trees form the opposite corners of the best rectangle. Both start at -1 to mean “no rectangle chosen yet.”

    static int treeOrder[20000]; //Each entry in treeOrder holds one integer—the index we use to look up a tree’s coordinates in x and y. The same tree can be fifth in the input and first when ordered from left to right.
    static int treeAtX[64001]; //Creates a lookup table. The index is an x-coordinate, and the value stored there is the tree's number in the input. 64001 gives us one slot for every possible x-coordinate, from 0 through 64000 inclusive. static gives the array a lifetime of the whole program. Since we provide no initializer, C starts every slot at 0, which we use to mean "no tree here"
    
    for (int i = 0; i < nTrees; i++) treeAtX[x[i]] = i + 1; //Look up tree number i to retrieve its x-coordinate and that is the slot to use in treeAtX for saving tree i, but tree saved is i + 1.
    
    int sortedCount = 0; //sortedCount tracks how many entries we've filled in treeOrder. It also gives us the next free index. The first tree we find goes into treeOrder[0]
    
    for (int xCoord = 0; xCoord <= 64000; xCoord++) { //Scanning treeAtX from 0 through 64000 visits occupied coordinates in left-to-right order. The <= includes the last possible coordinate.
        if (treeAtX[xCoord] == 0) continue;
        treeOrder[sortedCount++] = treeAtX[xCoord] - 1;
    }

    static int belowLeft[20000];

    for (int right = 1; right < sortedCount; ++right) {
        int rightTree = treeOrder[right];
        int rightY = y[rightTree];
        int belowRight = 0;

        for (int left = right - 1; left >= 0; --left) {
            int leftTree = treeOrder[left];
            int leftY  = y[leftTree];
            int difference = belowRight - belowLeft[left];
            int count = 2 + (difference < 0 ? -difference : difference);

            if (count >= minTrees && count < bestCount) {
                bestCount = count;
                bestI = leftTree;
                bestJ = rightTree;
            }

            if(leftY < rightY) ++belowRight;
            else ++belowLeft[left];
        }
    }

    FILE *output = fopen("artemis.out", "w");
    if (output == NULL ) return 1;
    
    return 0;
}