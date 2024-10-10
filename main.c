#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>

enum World_Size {
    WIDTH = 40,
    HEIGHT = 20
};

int main(void) {
    char enemy_armored = 'O', enemy_normal = 'U', enemy_bullet = '+';
    char player = 'A', player_bullet = '^', direction = 'l';
    char world[HEIGHT][WIDTH];
    char smoke = '@', key;
    
    int x, y, score = 0, total_enemies = 0;
    
    srand(time(NULL));
    
    printf("\n\n\n\t\t=======\tSPACE INVADER\t========\n\n");
    printf("\t\tOne ship to kill them all\n\n");
    printf("\t\tPress anything to play");
    getch();
    
    int running = 1;
    
    // Storing enemy position
    for(x = 0; x < WIDTH; x++) {
        for(y = 0; y < HEIGHT; y++) {
            if((y + 1) % 2 == 0 && y < 5 && x > 4 && x < WIDTH - 6 && x % 2 == 0) {
                world[y][x] = enemy_normal;
                total_enemies++;
            }
            
            else if((y + 1) % 2 == 0 && y >= 5 && y < 7 && x > 4 && x < WIDTH - 6 && x % 2 == 0) {
                world[y][x] = enemy_armored;
            }
            
            else {
                world[y][x] = ' ';
            }
        }
    }
    
    world[HEIGHT - 1][WIDTH / 2] = player; //Player position
    int curr_enemies = total_enemies;
    int n = 0;
    
    while(running) {
        system("clear");
        printf("\tScore: %d\n\n", score);
        
        // Initializing the world
        for(y = 0; y < HEIGHT; y++) {
            printf("|");
            for(x = 0; x < WIDTH; x++) {
                printf("%c", world[y][x]);
            }
            
            printf("|");
            printf("\n");
        }
        
        // Printing enemy bullets
        for(x = 0; x < WIDTH; x++) {
            for(y = 0; y < HEIGHT - 1; y++) {
                if((n + 1) % 10 == 0 && (world[y][x] == enemy_armored | world[y][x] == enemy_normal) && (world[y + 2][x] != enemy_armored & world[y + 2][x] != enemy_normal) && (rand() % 15) > 13) {
                    world[y + 1][x] = enemy_bullet;
                }
            }
        }
        
        // Moving the enemy and player`s bullets
        // Enemy bullet position
        for(x = 0; x < WIDTH; x++) {
            for(y = HEIGHT - 1; y >= 0; y--) {
                if(y == HEIGHT - 1 && world[y][x] == enemy_bullet) {
                    world[y][x] = ' ';
                }
                
                else if(world[y][x] == enemy_bullet && world[y + 1][x] != player && (n + 1) % 10 == 0) {
                    world[y + 1][x] = enemy_bullet;
                    world[y][x] = ' ';
                }
            }
        }
        
        // Player's bulllet position
        for(x = 0; x < WIDTH; x++) {
            for(y = 0; y < HEIGHT; y++) {
                if(y == 0 && world[y][x] == player_bullet) {
                    world[y][x] = ' ';
                }
                
                else if(world[y][x] == player_bullet && (world[y - 1][x] != enemy_normal && world[y - 1][x] != enemy_armored) && (n + 1) % 5 == 0) {
                    world[y][x] = ' ';
                    world[y - 1][x] = player_bullet;
                }
            }
        }
        
        // Bulllet collision detection
        // Enemy bullets
        for(y = HEIGHT - 1; y >= 0; y--) {
            for(x = 0; x < WIDTH; x++) {
                if(world[y][x] == enemy_bullet && world[y + 1][x] == player_bullet) {
                    world[y][x] = ' ';
                    world[y + 1][x] = smoke;
                }
                
                else if(world[y][x] == enemy_bullet && world[y + 1][x] == player && y < HEIGHT - 1) {
                    world[y][x] = ' ';
                    world[y + 1][x] = smoke;
                    running = 0;
                }
            }
        }
        
        // Player's bullets
        for(y = 0; y < HEIGHT - 1; y++) {
            for(x = 0; x < WIDTH; x++) {
                if(world[y][x] == player_bullet && world[y - 1][x] == enemy_bullet) {
                    world[y][x] = ' ';
                    world[y - 1][x] = smoke;
                }
                
                else if(world[y][x] == player_bullet && world[y - 1][x] == enemy_normal && y > 0) {
                    world[y][x] = ' ';
                    world[y - 1][x] = smoke;
                    score += 100;
                    curr_enemies--;
                }
                
                else if(world[y][x] == player_bullet && world[y - 1][x] == enemy_armored && y > 0) {
                    world[y][x] = ' ';
                    world[y - 1][x] = enemy_normal;
                    score += 50;
                    curr_enemies++;
                }
            }
        }
        
        
        // Checking if there is still enemies
        if(curr_enemies == 0) {
            running = 0;
        }
        
        // Enemy movement
        if(direction == 'l' && (n + 1) % 2 == 0) {
            for(y = 0; y < HEIGHT; y++) {
                for(x = 0; x < WIDTH; x++) {
                    if(x == 1 && (world[y][x] == enemy_normal | world[y][x] == enemy_armored)) {
                        direction = 'r';
                        break;
                    }
                    
                    else if(world[y][x] == enemy_normal && (world[y][x - 1] != enemy_normal | world[y][x - 1] != enemy_armored) && (n + 1) % 3 == 0) {
                        world[y][x - 1] = enemy_normal;
                        world[y][x] = ' ';
                    }
                    
                    else if(world[y][x] == enemy_armored && (world[y][x - 1] != enemy_armored | world[y][x - 1] != enemy_armored) && (n + 1) % 3 == 0) {
                        world[y][x - 1] = enemy_armored;
                        world[y][x] = ' ';
                    }
                }
            }
        }
        
        else if(direction == 'r' && (n + 1) % 2 == 0) {
            for(y = 0; y < HEIGHT; y++) {
                for(x = WIDTH - 1; x > 0; x--) {
                    if(x == WIDTH - 2 && (world[y][x] == enemy_normal | world[y][x] == enemy_armored)) {
                        direction = 'l';
                        break;
                    }
                    
                    else if(world[y][x] == enemy_normal && (world[y][x + 1] != enemy_normal | world[y][x + 1] != enemy_armored) && (n + 1) % 3 == 0) {
                        world[y][x + 1] = enemy_normal;
                        world[y][x] = ' ';
                    }
                    
                    else if(world[y][x] == enemy_armored && (world[y][x + 1] != enemy_normal | world[y][x + 1] != enemy_armored) && (n + 1) % 3 == 0) {
                        world[y][x + 1] = enemy_armored;
                        world[y][x] = ' ';
                    }
                }
            }
        }
        
        // Player control
        key = (kbhit()) ? (getch()) : ' ';
        
        if(key == 'a') {
            for(x = 0; x < WIDTH; x++) {
                if(world[HEIGHT - 1][x] == player && world[HEIGHT - 1][1] != player) {
                    world[HEIGHT - 1][x - 1] = player;
                    world[HEIGHT - 1][x] = ' ';
                }
            }
        }
        
        else if(key == 'd') {
            for(x = WIDTH - 1; x > 0; x--) {
                if(world[HEIGHT - 1][x] == player && world[HEIGHT - 1][WIDTH - 2] != player) {
                    world[HEIGHT - 1][x + 1] = player;
                    world[HEIGHT - 1][x] = ' ';
                }
            }
        }
        
        else if(key == 'k') {
            for(x = 0; x < WIDTH; x++) {
                if(world[HEIGHT - 1][x] == player && world[HEIGHT - 2][x] == ' ') {
                    world[HEIGHT - 2][x] = player_bullet;
                }
            }
        }
        
        else if(key == 'p') {
            system("clear");
            printf("\tCurrent Enemies: %d\n\tTotal Enemies: %d", curr_enemies, total_enemies);
            
            running = 0;
        }
        
        n++;
        usleep(2000);
    }
    
    if(curr_enemies == 0) {
        printf("\n\n\nYou've won... Congrats\n\n\n");
    }
    
    else {
        system("clear");
        printf("\nYou've lost\n");
        printf("\tScore: %d\n\n", score);
        
        // Initializing the world
        for(y = 0; y < HEIGHT; y++) {
            printf("|");
            for(x = 0; x < WIDTH; x++) {
                printf("%c", world[y][x]);
            }
            
            printf("|");
            printf("\n");
        }
    }
    
    return 0;
}
