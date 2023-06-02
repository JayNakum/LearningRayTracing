#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <time.h>

#define checkCudaErrors(val) check_cuda( (val), #val, __FILE__, __LINE__ )
void check_cuda(cudaError_t result, char const* const func, const char* const file, int const line)
{
    if (result)
    {
        std::cerr << "CUDA error [" << static_cast<unsigned int>(result) << "]: " <<
            file << "(" << line << ") '" << func << "' \n";

        cudaDeviceReset();
        exit(99);
    }
}

__global__ void render(float* fb, int max_x, int max_y)
{
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;

    if ((i >= max_x) || (j >= max_y)) return;

    int pixel_index = (3*j*max_x) + (3*i);
    fb[pixel_index + 0] = float(i) / max_x;
    fb[pixel_index + 1] = float(j) / max_y;
    fb[pixel_index + 2] = 0.2f;
}

int main()
{
    int nx = 1200;
    int ny = 600;

    int num_pixels = nx * ny;
    size_t fb_size = 3 * num_pixels * sizeof(float);

    // allocate FB
    float* fb = nullptr;
    checkCudaErrors(cudaMallocManaged((void**)&fb, fb_size));

    int tx = 8;
    int ty = 8;

    dim3 blocks(nx/tx+1, ny/ty+1);
    dim3 threads(tx, ty);

    clock_t start, stop;
    start = clock();

    render<<<blocks, threads>>>(fb, nx, ny);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());

    stop = clock();
    double time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    std::cerr << "Completed in " << time << " seconds." << std::endl;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            int pixel_index = (3 * j * nx) + (3 * i);
            float r = fb[pixel_index + 0];
            float g = fb[pixel_index + 1];
            float b = fb[pixel_index + 2];
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

    checkCudaErrors(cudaFree(fb));
}
