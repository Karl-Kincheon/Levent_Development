#include "Fast_Windows_Console.h"
#include "Queue_Example.h"

void draw_Queue(int x, int y, const Queue::Queue *q);

int main()
{
	srand(1234);

	FWC::init();

	Queue::Queue my_queue;
	Queue::init(&my_queue, 8);

	int x = 30;
	int y = 5;

	for (;;)
	{
		FWC::clear();
		//collect keyboard events
		FWC::update_Input();

		//push when D key is tapped, stack will resize if necessary
		//will not grow more than size 18 to stay within screen bounds
		if (FWC::key_State('S') == 1 && FWC::key_Last_State('S') == 0)
		{
			if (my_queue.n_data < 18)
			{
				//push a random number between 0 and 999
				int val = rand() % 1000;
				Queue::enqueue(&my_queue, val);
			}
		}

		//if the stack is not empty, pop when A key is tapped
		if (FWC::key_State('W') == 1 && FWC::key_Last_State('W') == 0)
		{
			if (my_queue.n_data > 0)
			{
				Queue::dequeue(&my_queue);
			}
		}

		//do not go out of screen bounds
		FWC::color(0x0F);
		FWC::put(1, y - 4, "QUEUE EXAMPLE");
		FWC::put(1, y - 3, "PRESS 'S' to enqueue, 'W' to dequeue!");
		draw_Queue(x, y, &my_queue);

		//present drawing
		FWC::present();
	}

	return 0;
}

void draw_Queue(int x, int y, const Queue::Queue *q)
{
	static char tmp[128];

	FWC::color(0xB0);
	for (int i = 0; i < q->size; i++)
	{
		sprintf(tmp, "%9d", q->data[i]);
		FWC::put(x, y + i, tmp);
	}

	int n_elements_before_offset = (q->offset + q->n_data) % q->size;
	int n_elements_after_offset = q->n_data - n_elements_before_offset;

	FWC::color(0xE0);
	for (int i = 0; i < q->n_data; i++)
	{
		sprintf(tmp, "%9d", q->data[(i + q->offset) % q->size]);
		FWC::put(x, y + ((i + q->offset) % q->size), tmp);
	}

	if (q->n_data == q->size)
	{
		sprintf(tmp, "n_data == size %2d ->", q->n_data);
		FWC::color(0x0F);
		FWC::put(x - strlen(tmp), y + s->n_data, tmp);

		FWC::color(0xC0);
		FWC::put(x, y + s->n_data, "!resize next push!");
	}
	else if (s->n_data == 0)
	{
		sprintf(tmp, "n_data %2d ->", s->n_data);
		FWC::color(0x0F);
		FWC::put(x - strlen(tmp), y, tmp);

		sprintf(tmp, "size %2d ->", s->size);
		FWC::color(0x0F);
		FWC::put(x - strlen(tmp), y + s->size, tmp);

		FWC::color(0xC0);
		FWC::put(x, y - 1, "!cannot pop!");
	}
	else
	{
		sprintf(tmp, "n_data %2d ->", s->n_data);
		FWC::color(0x0F);
		FWC::put(x - strlen(tmp), y + s->n_data, tmp);

		sprintf(tmp, "size %2d ->", s->size);
		FWC::color(0x0F);
		FWC::put(x - strlen(tmp), y + s->size, tmp);
	}

	if (s->n_data == 1)
	{
		sprintf(tmp, "<- %2d first and last", s->n_data - 1);
		FWC::color(0x0F);
		FWC::put(x + 10, y, tmp);
	}
	else if (s->n_data > 1)
	{
		sprintf(tmp, "<- %2d first", 0);
		FWC::color(0x0F);
		FWC::put(x + 9, y, tmp);

		sprintf(tmp, "<- %2d last", s->n_data - 1);
		FWC::color(0x0F);
		FWC::put(x + 9, y + s->n_data - 1, tmp);
	}
}
