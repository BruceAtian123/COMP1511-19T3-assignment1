// Assignment 1 19T3 COMP1511: CS Paint
// paint.c
//
// This program was written by Jinming(Patrick) Dong (z5211275)
// on 12/10/2019
//
// Version 1.0.0 (2019-10-08): Assignment released.

#include <stdio.h>

// Note: you may find the square root function (sqrt) from the math
// library useful for drawing ellipses in Stage 3 and Stage 4.
#include <math.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define WHITE 4

// IF YOU NEED MORE #defines ADD THEM HERE


// Provided helper functions:
// Display the canvas.
void displayCanvas(int canvas[N_ROWS][N_COLS]);

// Clear the canvas by setting every pixel to be white.
void clearCanvas(int canvas[N_ROWS][N_COLS]);

// Calculate the distance between two points.
// Note: you will only need this function for the Draw Ellipse command
// in Stages 3 and 4.
double distance(int row1, int col1, int row2, int col2);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
void drawLine(int canvas[N_ROWS][N_COLS],int start_row,int start_col,int length,int direction,int shade);
void drawSquare(int canvas[N_ROWS][N_COLS],int start_row,int start_col,int length,int direction,int shade);
void copyPaste(int canvas[N_ROWS][N_COLS],int start_row,int start_col,int length,int direction,int target_row,int target_col,int shade);
void drawEllipse(int canvas[N_ROWS][N_COLS],int focus_1_row,int focus_1_col,int focus_2_row,int focus_2_col,double length,int fill,int shade);
double squareDistance(int row1, int col1, int row2, int col2);


int main(void) {
    int canvas[N_ROWS][N_COLS];
    int instruction;
    int start_row;
    int start_col;
    int target_row;
    int target_col;
    double length;
    int direction;
    int shade = BLACK;
    int changeshade;
    int focus_1_row;
    int focus_1_col;
    int focus_2_row;
    int focus_2_col;
    int fill;

    clearCanvas(canvas);
    // TODO: Add your code here!

    // Hint: start by scanning in the command.
    //
    // If the command is the "Draw Line" command, scan in the rest of
    // the command (start row, start col, length, direction) and use
    // that information to draw a line on the canvas.
    //
    // Once your program can draw a line, add a loop to keep scanning
    // commands until you reach the end of input, and process each
    // command as you scan it.
    while(scanf("%d",&instruction)==1){
        if(instruction==1 || instruction==2){
            scanf("%d",&start_row);
            scanf("%d",&start_col);
            scanf("%lf",&length);
            scanf("%d",&direction);
        }
        if(instruction==3){
	        scanf("%d", &changeshade);
	        int newshade = shade+changeshade;
	        if(newshade > 4||newshade < 0){
	        
	        }
	        else{
	            shade+=changeshade;
	        }
	    }
	    if(instruction==4){
	        scanf("%d",&start_row);
            scanf("%d",&start_col);
            scanf("%lf",&length);
            scanf("%d",&direction);
            scanf("%d",&target_row);
            scanf("%d",&target_col);
	    }
	    if(instruction==0){
	        scanf("%d",&focus_1_row);
            scanf("%d",&focus_1_col);
            scanf("%d",&focus_2_row);
            scanf("%d",&focus_2_col);
            scanf("%lf",&length);
            scanf("%d",&fill);
	    }
        if (instruction == 1){
            if((start_row >= 0 && start_row < N_ROWS) && (start_col >= 0 && start_col < N_COLS)){
                drawLine(canvas, start_row, start_col, length, direction, shade);
            } 
        }
        else if (instruction == 2){
            if((start_row >= 0 && start_row < N_ROWS) && (start_col >= 0 && start_col < N_COLS)){
                drawSquare(canvas, start_row, start_col, length, direction, shade);
            } 
        }
        else if (instruction == 4){
            if((start_row >= 0 && start_row < N_ROWS) && (start_col >= 0 && start_col < N_COLS)){
                copyPaste(canvas, start_row, start_col, length, direction, target_row, target_col, shade);
            } 
        }
        else if (instruction == 0){
            if((focus_1_row >= 0 && focus_1_row < N_ROWS) && (focus_1_col >= 0 && focus_1_col < N_COLS) && (focus_2_row >= 0 && focus_2_row < N_ROWS) && (focus_2_col >= 0 && focus_2_col < N_COLS)){
                drawEllipse(canvas, focus_1_row, focus_1_col, focus_2_row, focus_2_col, length, fill, shade);
            } 
        }
    }
    
    displayCanvas(canvas);

    return 0;
}



// ADD CODE FOR YOUR FUNCTIONS HERE
void drawLine(int canvas[N_ROWS][N_COLS],int start_row,int start_col,int length,int direction,int shade){
    if(length<0){
        length = -1*length;
        direction += 180;
    }
    while(direction>=360){
        direction = direction % 360;
    }
    if(length==1){
        canvas[start_row][start_col] = shade;
    }
    else if(length==0){
        
    }
    else{
        if(direction==0){
            int row = start_row;
            int targetrow = row-length;
            while(row>targetrow && targetrow>=0 && targetrow<N_ROWS){
                canvas[row][start_col] = shade;
                row--;
            }
        }
        else if(direction==45){
            int row = start_row;
            int col = start_col;
            int targetrow = row-length;
            int targetcol = col+length;
            while(row>targetrow && col<targetcol && targetrow>=0 && targetrow<N_ROWS && targetcol>=0 && targetcol<N_COLS){
                canvas[row][col] = shade;
                row--;
                col++;
            }
        }
        else if(direction==90){
            int col = start_col;
            int targetcol = col+length;
            while(col<targetcol && targetcol>=0 && targetcol<N_COLS){
                canvas[start_row][col] = shade;
                col++;
            }
        }
        else if(direction==135){
            int row = start_row;
            int col = start_col;
            int targetrow = row+length;
            int targetcol = col+length;
            while(row<targetrow && col<targetcol && targetrow>=0 && targetrow<N_ROWS && targetcol>=0 && targetcol<N_COLS){
                canvas[row][col] = shade;
                row++;
                col++;
            }
        }
        else if(direction==180){
            int row = start_row;
            int targetrow = row+length;
            while(row<targetrow && targetrow>=0 && targetrow<N_ROWS){
                canvas[row][start_col] = shade;
                row++;
            }
        }
        else if(direction==225){
            int row = start_row;
            int col = start_col;
            int targetrow = row+length;
            int targetcol = col-length;
            while(row<targetrow && col>targetcol && targetrow>=0 && targetrow<N_ROWS && targetcol>=0 && targetcol<N_COLS){
                canvas[row][col] = shade;
                row++;
                col--;
            }
        }
        else if(direction==270){
            int col = start_col;
            int targetcol = col-length;
            while(col>targetcol && targetcol>=0 && targetcol<N_COLS){
                canvas[start_row][col] = shade;
                col--;
            }
        }
        else if(direction==315){
            int row = start_row;
            int col = start_col;
            int targetrow = row-length;
            int targetcol = col-length;
            while(row>targetrow && col>targetcol && targetrow>=0 && targetrow<N_ROWS && targetcol>=0 && targetcol<N_COLS){
                canvas[row][col] = shade;
                row--;
                col--;
            }
        }
    }
}

void drawSquare(int canvas[N_ROWS][N_COLS],int start_row,int start_col,int length,int direction,int shade){
    if(length<0){
        length = -1*length;
        direction += 180;
    }
    while(direction>=360){
        direction = direction % 360;
    }
    if(length==1){
        canvas[start_row][start_col] = shade;
    }
    else if(length==0){
        
    }
    else{
        if(direction==0 || direction==90 || direction==180 || direction==270){
            drawLine(canvas,start_row,start_col,length,direction,shade);
        }
        if(direction==45){
            int row = start_row;
            int col = start_col;
            int targetrow = row-length;
            int targetcol = col+length;
            while(row>targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col<targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row][col] = shade;
                    col++;
                }
                col = start_col;
                row--;
            }
        }
        else if(direction==135){
            int row = start_row;
            int col = start_col;
            int targetrow = row+length;
            int targetcol = col+length;
            while(row<targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col<targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row][col] = shade;
                    col++;
                }
                col = start_col;
                row++;
            }
        }
        else if(direction==225){
            int row = start_row;
            int col = start_col;
            int targetrow = row+length;
            int targetcol = col-length;
            while(row<targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col>targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row][col] = shade;
                    col--;
                }
                col = start_col;
                row++;
            }
        }
        else if(direction==315){
            int row = start_row;
            int col = start_col;
            int targetrow = row-length;
            int targetcol = col-length;
            while(row>targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col>targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row][col] = shade;
                    col--;
                }
                col = start_col;
                row--;
            }
        }
    }
}

void copyPaste(int canvas[N_ROWS][N_COLS],int start_row,int start_col,int length,int direction,int target_row,int target_col,int shade){
    int rowdiff = target_row-start_row;
    int coldiff = target_col-start_col;
    int oldcanvas[N_ROWS][N_COLS];
    for(int i = 0;i<N_ROWS;i++){
        for(int j = 0;j<N_COLS;j++){
            oldcanvas[i][j] = canvas[i][j];
        }
    }
    if(length<0){
        length = -1*length;
        direction += 180;
    }
    while(direction>=360){
        direction = direction % 360;
    }
    if(length==1){
        canvas[start_row+rowdiff][start_col+coldiff] = oldcanvas[start_row][start_col];
    }
    else if(length==0){
        
    }
    else{
        if(direction==0 || direction==90 || direction==180 || direction==270){
            if(direction==0){
            int row = start_row;
            int targetrow = row-length;
            while(row>targetrow && targetrow>=0 && targetrow<N_ROWS){
                canvas[row+rowdiff][start_col+coldiff] = oldcanvas[row][start_col];
                row--;
            }
        }
        else if(direction==90){
            int col = start_col;
            int targetcol = col+length;
            while(col<targetcol && targetcol>=0 && targetcol<N_COLS){
                canvas[start_row+rowdiff][col+coldiff] = oldcanvas[start_row][col];
                col++;
            }
        }
        else if(direction==180){
            int row = start_row;
            int targetrow = row+length;
            while(row<targetrow && targetrow>=0 && targetrow<N_ROWS){
                canvas[row+rowdiff][start_col+coldiff] = oldcanvas[row][start_col];
                row++;
            }
        }
        else if(direction==270){
            int col = start_col;
            int targetcol = col-length;
            while(col>targetcol && targetcol>=0 && targetcol<N_COLS){
                canvas[start_row+rowdiff][col+coldiff] = oldcanvas[start_row][col];
                col--;
            }
        }
        }
        if(direction==45){
            int row = start_row;
            int col = start_col;
            int targetrow = row-length;
            int targetcol = col+length;
            while(row>targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col<targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row+rowdiff][col+coldiff] = oldcanvas[row][col];
                    col++;
                }
                col = start_col;
                row--;
            }
        }
        else if(direction==135){
            int row = start_row;
            int col = start_col;
            int targetrow = row+length;
            int targetcol = col+length;
            while(row<targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col<targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row+rowdiff][col+coldiff] = oldcanvas[row][col];
                    col++;
                }
                col = start_col;
                row++;
            }
        }
        else if(direction==225){
            int row = start_row;
            int col = start_col;
            int targetrow = row+length;
            int targetcol = col-length;
            while(row<targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col>targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row+rowdiff][col+coldiff] = oldcanvas[row][col];
                    col--;
                }
                col = start_col;
                row++;
            }
        }
        else if(direction==315){
            int row = start_row;
            int col = start_col;
            int targetrow = row-length;
            int targetcol = col-length;
            while(row>targetrow && targetrow>=0 && targetrow<N_ROWS){
                while(col>targetcol && targetcol>=0 && targetcol<N_COLS){
                    canvas[row+rowdiff][col+coldiff] = oldcanvas[row][col];
                    col--;
                }
                col = start_col;
                row--;
            }
        }
    }
}

void drawEllipse(int canvas[N_ROWS][N_COLS],int focus_1_row,int focus_1_col,int focus_2_row,int focus_2_col,double length,int fill,int shade){
    int pixel_row = 0;
    int pixel_col = 0;
    if(fill!=0){
        while(pixel_row<N_ROWS){
            while(pixel_col<N_COLS){
                if(distance(focus_1_row,focus_1_col,pixel_row,pixel_col)+distance(focus_2_row,focus_2_col,pixel_row,pixel_col)<=2*length){
                    canvas[pixel_row][pixel_col] = shade;
                }
                pixel_col++;
            }
            pixel_col = 0;
            pixel_row++;
        }
    }
    else{
        while(pixel_row<N_ROWS){
            while(pixel_col<N_COLS){
                if(distance(focus_1_row,focus_1_col,pixel_row,pixel_col)+distance(focus_2_row,focus_2_col,pixel_row,pixel_col)<=2*length){
                    canvas[pixel_row][pixel_col] = shade;
                }
                pixel_col++;
            }
            pixel_col = 0;
            pixel_row++;
        }
        int oldcanvas[N_ROWS][N_COLS];
        for(int i = 0;i<N_ROWS;i++){
            for(int j = 0;j<N_COLS;j++){
                oldcanvas[i][j] = canvas[i][j];
            }
        }
        int i = 0;
        int j = 0;
        while(i<N_ROWS){
            while(j<N_COLS){
                if(oldcanvas[i][j]==shade){
                    if(i+1<N_ROWS){
                       if(oldcanvas[i+1][j]!=shade && oldcanvas[i+1][j]!=5){
                        oldcanvas[i][j] = 5;
                       }
                    }
                    if(i-1>=0){
                        if(oldcanvas[i-1][j]!=shade && oldcanvas[i-1][j]!=5){
                        oldcanvas[i][j] = 5;
                       }
                    }
                    if(j+1<N_COLS){
                       if(oldcanvas[i][j+1]!=shade && oldcanvas[i][j+1]!=5){
                        oldcanvas[i][j] = 5;
                       }
                    }
                    if(j-1>=0){
                        if(oldcanvas[i][j-1]!=shade && oldcanvas[i][j-1]!=5){
                        oldcanvas[i][j] = 5;
                       }
                    }
                    }
                    j++;
                }
                j = 0;
                i++;
            }
        for(int k = 0;k<N_ROWS;k++){
            for(int m = 0;m<N_COLS;m++){
                if(oldcanvas[k][m]==5){
                    canvas[k][m] = shade;
                }
                else{
                    canvas[k][m] = WHITE;
                }
            }
        }
        }
    }


// Displays the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the displayCanvas function.
void displayCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the clearCanvas function.
void clearCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}

// Calculate the distance between two points (row1, col1) and (row2, col2).
// Note: you will only need this function for the Draw Ellipse command
// in Stages 3 and 4.
double distance(int row1, int col1, int row2, int col2) {
    int row_dist = row2 - row1;
    int col_dist = col2 - col1;
    return sqrt((row_dist * row_dist) + (col_dist * col_dist));
}
