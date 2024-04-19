#include <SDL.h>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
	// khoi tao window va renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;

	enum Direction {
		DOWN,
		LEFT,
		RIGHT,
		UP
	};
	SDL_Rect head{ 500,500,10,10 };
	//snake body
	deque <SDL_Rect> rq;
	int size = 1;
	//apple container
	vector <SDL_Rect> apples;
	//apples spawn
	for (int i = 0; i < 100; i++) {
		apples.emplace_back(rand() % 100 * 10, rand() % 100 * 10, 10, 10);
	}
	// xu ly tac vu khi chay window
	bool running = true;
	int dir = 0;


	while (running) {
		// check inputs
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			if (e.key.keysym.sym == SDLK_DOWN) {
				dir = DOWN;
			}
			if (e.key.keysym.sym == SDLK_UP) {
				dir = UP;
			}
			if (e.key.keysym.sym == SDLK_LEFT) {
				dir = LEFT;
			}
			if (e.key.keysym.sym == SDLK_RIGHT) {
				dir = RIGHT;
			}
		}

		// Update the position of the head based on the direction
		switch (dir) {
		case DOWN:
			head.y += 5;
			break;
		case UP:
			head.y -= 5;
			break;
		case LEFT:
			head.x -= 5;
			break;
		case RIGHT:
			head.x += 5;
			break;
		}
		// collision detection
		for_each(apples.begin(), apples.end(), [&](auto& apple) {
			if (head.x == apple.x && head.y == apple.y) {
				size += 10;
				apple.x = -10;
				apple.y = -10;
			}
			});
		//collision detection snake body 
		//when snake touch its body
		for_each(rq.begin(), rq.end(), [&](auto& snake_segment) {
			if (head.x == snake_segment.x && head.y == snake_segment.y) {
				size = 1;
			}
			});
		// add newest head to the snake
		rq.push_front(head);
		while (rq.size() > size) {
			rq.pop_back();
		}


		//set color for window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderClear(renderer);

		//draw body
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for_each(rq.begin(), rq.end(), [&](auto& snake_segment) {
			SDL_RenderFillRect(renderer, &snake_segment);
			});
		//draw apples
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		for_each(rq.begin(), rq.end(), [&](auto& apple) {
			SDL_RenderFillRect(renderer, &apple);
			});
		//render window
		SDL_RenderPresent(renderer);
		SDL_Delay(25);
	}
	return 0;
}
