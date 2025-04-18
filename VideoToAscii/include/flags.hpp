#pragma once
//bits for each flag (arguments)
#define SOBEL_BIT 0
#define SHARPEN_BIT 1
#define GAUSSIAN_BIT 2


//flags
#define SOBEL_FLAG            (1 << SOBEL_BIT)
#define SHARPEN_FLAG      (1 << SHARPEN_BIT)
#define GAUSSIAN_FLAG     (1 << GAUSSIAN_BIT)