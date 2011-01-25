// allocate
int words = (W * H + 3) / 4;
int *red   = new int[words];
int *blue  = new int[words];
int *green = new int[words];
int *alpha = new int[words];

// find the right byte
int pixel = i * W + j;
int word = pixel / 4;
int byte = pixel % 4;
int mask = ~(0xFF << byte * 8);
color = (color & 0xFF) << byte * 8;

// set the color value
red[word]   = red[word]   & mask | color;
blue[word]  = blue[word]  & mask | color;
green[word] = green[word] & mask | color;
alpha[word] = alpha[word] & mask | color;			
	
// get the color value
red[word] >> (byte * 8) & 0xFF;
blue[word] >> (byte * 8) & 0xFF;
green[word] >> (byte * 8) & 0xFF;
alpha[word] >> (byte * 8) & 0xFF;