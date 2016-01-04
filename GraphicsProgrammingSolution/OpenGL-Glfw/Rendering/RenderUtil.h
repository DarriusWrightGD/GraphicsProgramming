class RenderUtil
{
public:
	static void FlipY(unsigned char * image, int width, int height, int channels)
	{
		for (signed int h = 0u; h * 2 < height; h++)
		{
			auto pixel1 = h * width * channels;
			auto pixel2 = (height - 1 - h) * width * channels;
			for (size_t w = width * channels; w > 0; w--)
			{
				auto temp = image[pixel1];
				image[pixel1] = image[pixel2];
				image[pixel2] = temp;
				pixel1++;
				pixel2++;
			}
		}
	}

};