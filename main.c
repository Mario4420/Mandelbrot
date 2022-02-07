#include <stdio.h>
#include <stdlib.h> 
#include <SDL2/SDL.h>

#define WINDOW_SIZE 600

double fmap(double x, double in_min, double in_max, double out_min, double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(){

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Mandelbrot",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_SIZE,
                                          WINDOW_SIZE,
                                          SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	double x0; 
	double y0;
	double x;
	float xtemp; 
    double y;

	int iter; 
	int maxIters =  1000; 

	for(;;){
		SDL_Event event;
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				break; 
			}
		}
		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		SDL_RenderClear(renderer);
		for(int pY = 0; pY < WINDOW_SIZE; pY++){
			for(int pX = 0; pX < WINDOW_SIZE; pX++){
				x0 = fmap(pX, 0, WINDOW_SIZE, -2, 0.47);
				y0 = fmap(pY, 0, WINDOW_SIZE, -1.12, 1.12);
				x = 0.0; 
				y = 0.0; 
				iter = 0; 
				while((x*x + y*y) <= 2*2 && iter < maxIters){
					xtemp = x*x - y*y + x0;
					y = 2*x*y + y0; 
					x = xtemp; 
					iter++;
				}
				SDL_SetRenderDrawColor(renderer, 
									   map(iter, 0, maxIters, 0, 255), 
									   map(iter, 0, maxIters, 0, 255), 
									   map(iter, 0, maxIters, 0, 255), 
									   map(iter, 0, maxIters, 0, 255)); 

				SDL_RenderDrawPoint(renderer, pX, pY); 
			}
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(16); 
	}
}
