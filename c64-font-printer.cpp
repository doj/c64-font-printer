#include <cstring>
#include <cstdio>
#include <stdint.h>
#include <cassert>

uint8_t ascii_to_screencode(const uint8_t c)
{
  if (c >= 'A' && c <= 'Z')
    return c - 'A' + 0x41;
  if (c >= 'a' && c <= 'z')
    return c - 'a' + 1;
  switch(c)
    {
    case '@': return 0;
    case '[': return 0x1b;
      // 0x1c // pound
    case ']': return 0x1d;
    case '^': return 0x1e;
    case '~': return 0x1f;
    case '|': return 0x42;
    case '\\': return 0x4d;
    }
  return c;
}

void print1(const unsigned u)
{
  printf("+");
  for(unsigned i = 0; i < u; ++i)
    printf("--------+");
  printf("\n");
}

void printrow(const uint8_t *s, const unsigned slen, const uint8_t *font, const unsigned row)
{
  assert(s);
  assert(font);
  printf("|");
  for(unsigned i = 0; i < slen; ++i)
    {
      const uint8_t ch = s[i];
      const uint8_t pixel = font[ch * 8 + row];
      uint8_t mask = 128;
      for(unsigned j = 0; j < 8; ++j)
	{
	  printf("%c", (pixel & mask) ? '*' : '.');
	  mask >>= 1;
	}
      printf("|");
    }
  printf("\n");
}

void print(uint8_t *s, const unsigned slen, const uint8_t *font)
{
  assert(s);
  assert(font);

  print1(slen);
  for(unsigned r = 0; r < 8; ++r)
    printrow(s, slen, font, r);
  print1(slen);
  printf("\n");
}

void fontdump(const uint8_t *font)
{
  for(unsigned i = 0; i < 256; i += 8)
    {
      uint8_t s[8];
      for(unsigned j = 0; j < 8; ++j)
	{
	  printf("    %02X   ", i+j);
	  s[j] = i+j;
	}
      printf("\n");
      print(s, 8, font);
    }
}

int main(int argc, char **argv)
{
  if (argc < 2)
    {
      printf("usage: c64-font-printer 'text'+\n");
      return 1;
    }

  const uint8_t c64_font[] =
    {
      0x3c, 0x66, 0x6e, 0x6e, 0x60, 0x62, 0x3c, 0x00,
      0x18, 0x3c, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x00,
      0x7c, 0x66, 0x66, 0x7c, 0x66, 0x66, 0x7c, 0x00,
      0x3c, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3c, 0x00,
      0x78, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0x78, 0x00,
      0x7e, 0x60, 0x60, 0x78, 0x60, 0x60, 0x7e, 0x00,
      0x7e, 0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x00,
      0x3c, 0x66, 0x60, 0x6e, 0x66, 0x66, 0x3c, 0x00,
      0x66, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x00,
      0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00,
      0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x6c, 0x38, 0x00,
      0x66, 0x6c, 0x78, 0x70, 0x78, 0x6c, 0x66, 0x00,
      0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x00,
      0x63, 0x77, 0x7f, 0x6b, 0x63, 0x63, 0x63, 0x00,
      0x66, 0x76, 0x7e, 0x7e, 0x6e, 0x66, 0x66, 0x00,
      0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00,
      0x7c, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0x00,
      0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x0e, 0x00,
      0x7c, 0x66, 0x66, 0x7c, 0x78, 0x6c, 0x66, 0x00,
      0x3c, 0x66, 0x60, 0x3c, 0x06, 0x66, 0x3c, 0x00,
      0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,
      0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00,
      0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x00,
      0x63, 0x63, 0x63, 0x6b, 0x7f, 0x77, 0x63, 0x00,
      0x66, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0x66, 0x00,
      0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x00,
      0x7e, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x7e, 0x00,
      0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00,
      0x0c, 0x12, 0x30, 0x7c, 0x30, 0x62, 0xfc, 0x00,
      0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c, 0x00,
      0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18,
      0x00, 0x10, 0x30, 0x7f, 0x7f, 0x30, 0x10, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00,
      0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x66, 0x66, 0xff, 0x66, 0xff, 0x66, 0x66, 0x00,
      0x18, 0x3e, 0x60, 0x3c, 0x06, 0x7c, 0x18, 0x00,
      0x62, 0x66, 0x0c, 0x18, 0x30, 0x66, 0x46, 0x00,
      0x3c, 0x66, 0x3c, 0x38, 0x67, 0x66, 0x3f, 0x00,
      0x06, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x0c, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x00,
      0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x00,
      0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00,
      0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30,
      0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
      0x00, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x00,
      0x3c, 0x66, 0x6e, 0x76, 0x66, 0x66, 0x3c, 0x00,
      0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7e, 0x00,
      0x3c, 0x66, 0x06, 0x0c, 0x30, 0x60, 0x7e, 0x00,
      0x3c, 0x66, 0x06, 0x1c, 0x06, 0x66, 0x3c, 0x00,
      0x06, 0x0e, 0x1e, 0x66, 0x7f, 0x06, 0x06, 0x00,
      0x7e, 0x60, 0x7c, 0x06, 0x06, 0x66, 0x3c, 0x00,
      0x3c, 0x66, 0x60, 0x7c, 0x66, 0x66, 0x3c, 0x00,
      0x7e, 0x66, 0x0c, 0x18, 0x18, 0x18, 0x18, 0x00,
      0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x3c, 0x00,
      0x3c, 0x66, 0x66, 0x3e, 0x06, 0x66, 0x3c, 0x00,
      0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00,
      0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30,
      0x0e, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0e, 0x00,
      0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x00, 0x00,
      0x70, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x70, 0x00,
      0x3c, 0x66, 0x06, 0x0c, 0x18, 0x00, 0x18, 0x00,
      0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
      0x08, 0x1c, 0x3e, 0x7f, 0x7f, 0x1c, 0x3e, 0x00,
      0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
      0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
      0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
      0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
      0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
      0x00, 0x00, 0x00, 0xe0, 0xf0, 0x38, 0x18, 0x18,
      0x18, 0x18, 0x1c, 0x0f, 0x07, 0x00, 0x00, 0x00,
      0x18, 0x18, 0x38, 0xf0, 0xe0, 0x00, 0x00, 0x00,
      0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xff,
      0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03,
      0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0,
      0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
      0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
      0x00, 0x3c, 0x7e, 0x7e, 0x7e, 0x7e, 0x3c, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
      0x36, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c, 0x08, 0x00,
      0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
      0x00, 0x00, 0x00, 0x07, 0x0f, 0x1c, 0x18, 0x18,
      0xc3, 0xe7, 0x7e, 0x3c, 0x3c, 0x7e, 0xe7, 0xc3,
      0x00, 0x3c, 0x7e, 0x66, 0x66, 0x7e, 0x3c, 0x00,
      0x18, 0x18, 0x66, 0x66, 0x18, 0x18, 0x3c, 0x00,
      0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
      0x08, 0x1c, 0x3e, 0x7f, 0x3e, 0x1c, 0x08, 0x00,
      0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
      0xc0, 0xc0, 0x30, 0x30, 0xc0, 0xc0, 0x30, 0x30,
      0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x03, 0x3e, 0x76, 0x36, 0x36, 0x00,
      0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
      0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
      0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
      0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33,
      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
      0x00, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0x33, 0x33,
      0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80,
      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
      0x18, 0x18, 0x18, 0x1f, 0x1f, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f,
      0x18, 0x18, 0x18, 0x1f, 0x1f, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xf8, 0xf8, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
      0x00, 0x00, 0x00, 0x1f, 0x1f, 0x18, 0x18, 0x18,
      0x18, 0x18, 0x18, 0xff, 0xff, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xff, 0xff, 0x18, 0x18, 0x18,
      0x18, 0x18, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x18,
      0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
      0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
      0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
      0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0xff,
      0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0,
      0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00,
      0x18, 0x18, 0x18, 0xf8, 0xf8, 0x00, 0x00, 0x00,
      0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00,
      0xf0, 0xf0, 0xf0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0f,
      0xc3, 0x99, 0x91, 0x91, 0x9f, 0x99, 0xc3, 0xff,
      0xe7, 0xc3, 0x99, 0x81, 0x99, 0x99, 0x99, 0xff,
      0x83, 0x99, 0x99, 0x83, 0x99, 0x99, 0x83, 0xff,
      0xc3, 0x99, 0x9f, 0x9f, 0x9f, 0x99, 0xc3, 0xff,
      0x87, 0x93, 0x99, 0x99, 0x99, 0x93, 0x87, 0xff,
      0x81, 0x9f, 0x9f, 0x87, 0x9f, 0x9f, 0x81, 0xff,
      0x81, 0x9f, 0x9f, 0x87, 0x9f, 0x9f, 0x9f, 0xff,
      0xc3, 0x99, 0x9f, 0x91, 0x99, 0x99, 0xc3, 0xff,
      0x99, 0x99, 0x99, 0x81, 0x99, 0x99, 0x99, 0xff,
      0xc3, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xc3, 0xff,
      0xe1, 0xf3, 0xf3, 0xf3, 0xf3, 0x93, 0xc7, 0xff,
      0x99, 0x93, 0x87, 0x8f, 0x87, 0x93, 0x99, 0xff,
      0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x81, 0xff,
      0x9c, 0x88, 0x80, 0x94, 0x9c, 0x9c, 0x9c, 0xff,
      0x99, 0x89, 0x81, 0x81, 0x91, 0x99, 0x99, 0xff,
      0xc3, 0x99, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xff,
      0x83, 0x99, 0x99, 0x83, 0x9f, 0x9f, 0x9f, 0xff,
      0xc3, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xf1, 0xff,
      0x83, 0x99, 0x99, 0x83, 0x87, 0x93, 0x99, 0xff,
      0xc3, 0x99, 0x9f, 0xc3, 0xf9, 0x99, 0xc3, 0xff,
      0x81, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff,
      0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xff,
      0x99, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xe7, 0xff,
      0x9c, 0x9c, 0x9c, 0x94, 0x80, 0x88, 0x9c, 0xff,
      0x99, 0x99, 0xc3, 0xe7, 0xc3, 0x99, 0x99, 0xff,
      0x99, 0x99, 0x99, 0xc3, 0xe7, 0xe7, 0xe7, 0xff,
      0x81, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x81, 0xff,
      0xc3, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xc3, 0xff,
      0xf3, 0xed, 0xcf, 0x83, 0xcf, 0x9d, 0x03, 0xff,
      0xc3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xc3, 0xff,
      0xff, 0xe7, 0xc3, 0x81, 0xe7, 0xe7, 0xe7, 0xe7,
      0xff, 0xef, 0xcf, 0x80, 0x80, 0xcf, 0xef, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe7, 0xff,
      0x99, 0x99, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x99, 0x99, 0x00, 0x99, 0x00, 0x99, 0x99, 0xff,
      0xe7, 0xc1, 0x9f, 0xc3, 0xf9, 0x83, 0xe7, 0xff,
      0x9d, 0x99, 0xf3, 0xe7, 0xcf, 0x99, 0xb9, 0xff,
      0xc3, 0x99, 0xc3, 0xc7, 0x98, 0x99, 0xc0, 0xff,
      0xf9, 0xf3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xf3, 0xe7, 0xcf, 0xcf, 0xcf, 0xe7, 0xf3, 0xff,
      0xcf, 0xe7, 0xf3, 0xf3, 0xf3, 0xe7, 0xcf, 0xff,
      0xff, 0x99, 0xc3, 0x00, 0xc3, 0x99, 0xff, 0xff,
      0xff, 0xe7, 0xe7, 0x81, 0xe7, 0xe7, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xcf,
      0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff,
      0xff, 0xfc, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0xff,
      0xc3, 0x99, 0x91, 0x89, 0x99, 0x99, 0xc3, 0xff,
      0xe7, 0xe7, 0xc7, 0xe7, 0xe7, 0xe7, 0x81, 0xff,
      0xc3, 0x99, 0xf9, 0xf3, 0xcf, 0x9f, 0x81, 0xff,
      0xc3, 0x99, 0xf9, 0xe3, 0xf9, 0x99, 0xc3, 0xff,
      0xf9, 0xf1, 0xe1, 0x99, 0x80, 0xf9, 0xf9, 0xff,
      0x81, 0x9f, 0x83, 0xf9, 0xf9, 0x99, 0xc3, 0xff,
      0xc3, 0x99, 0x9f, 0x83, 0x99, 0x99, 0xc3, 0xff,
      0x81, 0x99, 0xf3, 0xe7, 0xe7, 0xe7, 0xe7, 0xff,
      0xc3, 0x99, 0x99, 0xc3, 0x99, 0x99, 0xc3, 0xff,
      0xc3, 0x99, 0x99, 0xc1, 0xf9, 0x99, 0xc3, 0xff,
      0xff, 0xff, 0xe7, 0xff, 0xff, 0xe7, 0xff, 0xff,
      0xff, 0xff, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xcf,
      0xf1, 0xe7, 0xcf, 0x9f, 0xcf, 0xe7, 0xf1, 0xff,
      0xff, 0xff, 0x81, 0xff, 0x81, 0xff, 0xff, 0xff,
      0x8f, 0xe7, 0xf3, 0xf9, 0xf3, 0xe7, 0x8f, 0xff,
      0xc3, 0x99, 0xf9, 0xf3, 0xe7, 0xff, 0xe7, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xf7, 0xe3, 0xc1, 0x80, 0x80, 0xe3, 0xc1, 0xff,
      0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
      0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
      0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf,
      0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3,
      0xff, 0xff, 0xff, 0x1f, 0x0f, 0xc7, 0xe7, 0xe7,
      0xe7, 0xe7, 0xe3, 0xf0, 0xf8, 0xff, 0xff, 0xff,
      0xe7, 0xe7, 0xc7, 0x0f, 0x1f, 0xff, 0xff, 0xff,
      0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00,
      0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8, 0xfc,
      0xfc, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0x1f, 0x3f,
      0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
      0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
      0xff, 0xc3, 0x81, 0x81, 0x81, 0x81, 0xc3, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff,
      0xc9, 0x80, 0x80, 0x80, 0xc1, 0xe3, 0xf7, 0xff,
      0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f,
      0xff, 0xff, 0xff, 0xf8, 0xf0, 0xe3, 0xe7, 0xe7,
      0x3c, 0x18, 0x81, 0xc3, 0xc3, 0x81, 0x18, 0x3c,
      0xff, 0xc3, 0x81, 0x99, 0x99, 0x81, 0xc3, 0xff,
      0xe7, 0xe7, 0x99, 0x99, 0xe7, 0xe7, 0xc3, 0xff,
      0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9,
      0xf7, 0xe3, 0xc1, 0x80, 0xc1, 0xe3, 0xf7, 0xff,
      0xe7, 0xe7, 0xe7, 0x00, 0x00, 0xe7, 0xe7, 0xe7,
      0x3f, 0x3f, 0xcf, 0xcf, 0x3f, 0x3f, 0xcf, 0xcf,
      0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
      0xff, 0xff, 0xfc, 0xc1, 0x89, 0xc9, 0xc9, 0xff,
      0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
      0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
      0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
      0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
      0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc,
      0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
      0xff, 0xff, 0xff, 0xff, 0x33, 0x33, 0xcc, 0xcc,
      0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f,
      0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
      0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7,
      0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0,
      0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0x07, 0x07, 0xe7, 0xe7, 0xe7,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
      0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7,
      0xe7, 0xe7, 0xe7, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xe7, 0xe7, 0xe7,
      0xe7, 0xe7, 0xe7, 0x07, 0x07, 0xe7, 0xe7, 0xe7,
      0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
      0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
      0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
      0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
      0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00,
      0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f,
      0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff,
      0xe7, 0xe7, 0xe7, 0x07, 0x07, 0xff, 0xff, 0xff,
      0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff,
      0x0f, 0x0f, 0x0f, 0x0f, 0xf0, 0xf0, 0xf0, 0xf0,
      0x3c, 0x66, 0x6e, 0x6e, 0x60, 0x62, 0x3c, 0x00,
      0x00, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x3e, 0x00,
      0x00, 0x60, 0x60, 0x7c, 0x66, 0x66, 0x7c, 0x00,
      0x00, 0x00, 0x3c, 0x60, 0x60, 0x60, 0x3c, 0x00,
      0x00, 0x06, 0x06, 0x3e, 0x66, 0x66, 0x3e, 0x00,
      0x00, 0x00, 0x3c, 0x66, 0x7e, 0x60, 0x3c, 0x00,
      0x00, 0x0e, 0x18, 0x3e, 0x18, 0x18, 0x18, 0x00,
      0x00, 0x00, 0x3e, 0x66, 0x66, 0x3e, 0x06, 0x7c,
      0x00, 0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x00,
      0x00, 0x18, 0x00, 0x38, 0x18, 0x18, 0x3c, 0x00,
      0x00, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x3c,
      0x00, 0x60, 0x60, 0x6c, 0x78, 0x6c, 0x66, 0x00,
      0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00,
      0x00, 0x00, 0x66, 0x7f, 0x7f, 0x6b, 0x63, 0x00,
      0x00, 0x00, 0x7c, 0x66, 0x66, 0x66, 0x66, 0x00,
      0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x3c, 0x00,
      0x00, 0x00, 0x7c, 0x66, 0x66, 0x7c, 0x60, 0x60,
      0x00, 0x00, 0x3e, 0x66, 0x66, 0x3e, 0x06, 0x06,
      0x00, 0x00, 0x7c, 0x66, 0x60, 0x60, 0x60, 0x00,
      0x00, 0x00, 0x3e, 0x60, 0x3c, 0x06, 0x7c, 0x00,
      0x00, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x0e, 0x00,
      0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3e, 0x00,
      0x00, 0x00, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x00,
      0x00, 0x00, 0x63, 0x6b, 0x7f, 0x3e, 0x36, 0x00,
      0x00, 0x00, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0x00,
      0x00, 0x00, 0x66, 0x66, 0x66, 0x3e, 0x0c, 0x78,
      0x00, 0x00, 0x7e, 0x0c, 0x18, 0x30, 0x7e, 0x00,
      0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00,
      0x0c, 0x12, 0x30, 0x7c, 0x30, 0x62, 0xfc, 0x00,
      0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c, 0x00,
      0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18,
      0x00, 0x10, 0x30, 0x7f, 0x7f, 0x30, 0x10, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00,
      0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x66, 0x66, 0xff, 0x66, 0xff, 0x66, 0x66, 0x00,
      0x18, 0x3e, 0x60, 0x3c, 0x06, 0x7c, 0x18, 0x00,
      0x62, 0x66, 0x0c, 0x18, 0x30, 0x66, 0x46, 0x00,
      0x3c, 0x66, 0x3c, 0x38, 0x67, 0x66, 0x3f, 0x00,
      0x06, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x0c, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x00,
      0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x00,
      0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00,
      0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30,
      0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
      0x00, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x00,
      0x3c, 0x66, 0x6e, 0x76, 0x66, 0x66, 0x3c, 0x00,
      0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7e, 0x00,
      0x3c, 0x66, 0x06, 0x0c, 0x30, 0x60, 0x7e, 0x00,
      0x3c, 0x66, 0x06, 0x1c, 0x06, 0x66, 0x3c, 0x00,
      0x06, 0x0e, 0x1e, 0x66, 0x7f, 0x06, 0x06, 0x00,
      0x7e, 0x60, 0x7c, 0x06, 0x06, 0x66, 0x3c, 0x00,
      0x3c, 0x66, 0x60, 0x7c, 0x66, 0x66, 0x3c, 0x00,
      0x7e, 0x66, 0x0c, 0x18, 0x18, 0x18, 0x18, 0x00,
      0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x3c, 0x00,
      0x3c, 0x66, 0x66, 0x3e, 0x06, 0x66, 0x3c, 0x00,
      0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00,
      0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30,
      0x0e, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0e, 0x00,
      0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x00, 0x00,
      0x70, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x70, 0x00,
      0x3c, 0x66, 0x06, 0x0c, 0x18, 0x00, 0x18, 0x00,
      0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
      0x18, 0x3c, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x00,
      0x7c, 0x66, 0x66, 0x7c, 0x66, 0x66, 0x7c, 0x00,
      0x3c, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3c, 0x00,
      0x78, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0x78, 0x00,
      0x7e, 0x60, 0x60, 0x78, 0x60, 0x60, 0x7e, 0x00,
      0x7e, 0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x00,
      0x3c, 0x66, 0x60, 0x6e, 0x66, 0x66, 0x3c, 0x00,
      0x66, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x00,
      0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00,
      0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x6c, 0x38, 0x00,
      0x66, 0x6c, 0x78, 0x70, 0x78, 0x6c, 0x66, 0x00,
      0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x00,
      0x63, 0x77, 0x7f, 0x6b, 0x63, 0x63, 0x63, 0x00,
      0x66, 0x76, 0x7e, 0x7e, 0x6e, 0x66, 0x66, 0x00,
      0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00,
      0x7c, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0x00,
      0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x0e, 0x00,
      0x7c, 0x66, 0x66, 0x7c, 0x78, 0x6c, 0x66, 0x00,
      0x3c, 0x66, 0x60, 0x3c, 0x06, 0x66, 0x3c, 0x00,
      0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,
      0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00,
      0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x00,
      0x63, 0x63, 0x63, 0x6b, 0x7f, 0x77, 0x63, 0x00,
      0x66, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0x66, 0x00,
      0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x00,
      0x7e, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x7e, 0x00,
      0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
      0xc0, 0xc0, 0x30, 0x30, 0xc0, 0xc0, 0x30, 0x30,
      0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
      0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc,
      0x33, 0x99, 0xcc, 0x66, 0x33, 0x99, 0xcc, 0x66,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
      0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
      0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
      0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33,
      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
      0x00, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0x33, 0x33,
      0xcc, 0x99, 0x33, 0x66, 0xcc, 0x99, 0x33, 0x66,
      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
      0x18, 0x18, 0x18, 0x1f, 0x1f, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f,
      0x18, 0x18, 0x18, 0x1f, 0x1f, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xf8, 0xf8, 0x18, 0x18, 0x18,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
      0x00, 0x00, 0x00, 0x1f, 0x1f, 0x18, 0x18, 0x18,
      0x18, 0x18, 0x18, 0xff, 0xff, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0xff, 0xff, 0x18, 0x18, 0x18,
      0x18, 0x18, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x18,
      0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
      0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
      0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
      0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
      0x01, 0x03, 0x06, 0x6c, 0x78, 0x70, 0x60, 0x00,
      0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0,
      0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00,
      0x18, 0x18, 0x18, 0xf8, 0xf8, 0x00, 0x00, 0x00,
      0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00,
      0xf0, 0xf0, 0xf0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0f,
      0xc3, 0x99, 0x91, 0x91, 0x9f, 0x99, 0xc3, 0xff,
      0xff, 0xff, 0xc3, 0xf9, 0xc1, 0x99, 0xc1, 0xff,
      0xff, 0x9f, 0x9f, 0x83, 0x99, 0x99, 0x83, 0xff,
      0xff, 0xff, 0xc3, 0x9f, 0x9f, 0x9f, 0xc3, 0xff,
      0xff, 0xf9, 0xf9, 0xc1, 0x99, 0x99, 0xc1, 0xff,
      0xff, 0xff, 0xc3, 0x99, 0x81, 0x9f, 0xc3, 0xff,
      0xff, 0xf1, 0xe7, 0xc1, 0xe7, 0xe7, 0xe7, 0xff,
      0xff, 0xff, 0xc1, 0x99, 0x99, 0xc1, 0xf9, 0x83,
      0xff, 0x9f, 0x9f, 0x83, 0x99, 0x99, 0x99, 0xff,
      0xff, 0xe7, 0xff, 0xc7, 0xe7, 0xe7, 0xc3, 0xff,
      0xff, 0xf9, 0xff, 0xf9, 0xf9, 0xf9, 0xf9, 0xc3,
      0xff, 0x9f, 0x9f, 0x93, 0x87, 0x93, 0x99, 0xff,
      0xff, 0xc7, 0xe7, 0xe7, 0xe7, 0xe7, 0xc3, 0xff,
      0xff, 0xff, 0x99, 0x80, 0x80, 0x94, 0x9c, 0xff,
      0xff, 0xff, 0x83, 0x99, 0x99, 0x99, 0x99, 0xff,
      0xff, 0xff, 0xc3, 0x99, 0x99, 0x99, 0xc3, 0xff,
      0xff, 0xff, 0x83, 0x99, 0x99, 0x83, 0x9f, 0x9f,
      0xff, 0xff, 0xc1, 0x99, 0x99, 0xc1, 0xf9, 0xf9,
      0xff, 0xff, 0x83, 0x99, 0x9f, 0x9f, 0x9f, 0xff,
      0xff, 0xff, 0xc1, 0x9f, 0xc3, 0xf9, 0x83, 0xff,
      0xff, 0xe7, 0x81, 0xe7, 0xe7, 0xe7, 0xf1, 0xff,
      0xff, 0xff, 0x99, 0x99, 0x99, 0x99, 0xc1, 0xff,
      0xff, 0xff, 0x99, 0x99, 0x99, 0xc3, 0xe7, 0xff,
      0xff, 0xff, 0x9c, 0x94, 0x80, 0xc1, 0xc9, 0xff,
      0xff, 0xff, 0x99, 0xc3, 0xe7, 0xc3, 0x99, 0xff,
      0xff, 0xff, 0x99, 0x99, 0x99, 0xc1, 0xf3, 0x87,
      0xff, 0xff, 0x81, 0xf3, 0xe7, 0xcf, 0x81, 0xff,
      0xc3, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xc3, 0xff,
      0xf3, 0xed, 0xcf, 0x83, 0xcf, 0x9d, 0x03, 0xff,
      0xc3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xc3, 0xff,
      0xff, 0xe7, 0xc3, 0x81, 0xe7, 0xe7, 0xe7, 0xe7,
      0xff, 0xef, 0xcf, 0x80, 0x80, 0xcf, 0xef, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe7, 0xff,
      0x99, 0x99, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x99, 0x99, 0x00, 0x99, 0x00, 0x99, 0x99, 0xff,
      0xe7, 0xc1, 0x9f, 0xc3, 0xf9, 0x83, 0xe7, 0xff,
      0x9d, 0x99, 0xf3, 0xe7, 0xcf, 0x99, 0xb9, 0xff,
      0xc3, 0x99, 0xc3, 0xc7, 0x98, 0x99, 0xc0, 0xff,
      0xf9, 0xf3, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xf3, 0xe7, 0xcf, 0xcf, 0xcf, 0xe7, 0xf3, 0xff,
      0xcf, 0xe7, 0xf3, 0xf3, 0xf3, 0xe7, 0xcf, 0xff,
      0xff, 0x99, 0xc3, 0x00, 0xc3, 0x99, 0xff, 0xff,
      0xff, 0xe7, 0xe7, 0x81, 0xe7, 0xe7, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xcf,
      0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff,
      0xff, 0xfc, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0xff,
      0xc3, 0x99, 0x91, 0x89, 0x99, 0x99, 0xc3, 0xff,
      0xe7, 0xe7, 0xc7, 0xe7, 0xe7, 0xe7, 0x81, 0xff,
      0xc3, 0x99, 0xf9, 0xf3, 0xcf, 0x9f, 0x81, 0xff,
      0xc3, 0x99, 0xf9, 0xe3, 0xf9, 0x99, 0xc3, 0xff,
      0xf9, 0xf1, 0xe1, 0x99, 0x80, 0xf9, 0xf9, 0xff,
      0x81, 0x9f, 0x83, 0xf9, 0xf9, 0x99, 0xc3, 0xff,
      0xc3, 0x99, 0x9f, 0x83, 0x99, 0x99, 0xc3, 0xff,
      0x81, 0x99, 0xf3, 0xe7, 0xe7, 0xe7, 0xe7, 0xff,
      0xc3, 0x99, 0x99, 0xc3, 0x99, 0x99, 0xc3, 0xff,
      0xc3, 0x99, 0x99, 0xc1, 0xf9, 0x99, 0xc3, 0xff,
      0xff, 0xff, 0xe7, 0xff, 0xff, 0xe7, 0xff, 0xff,
      0xff, 0xff, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xcf,
      0xf1, 0xe7, 0xcf, 0x9f, 0xcf, 0xe7, 0xf1, 0xff,
      0xff, 0xff, 0x81, 0xff, 0x81, 0xff, 0xff, 0xff,
      0x8f, 0xe7, 0xf3, 0xf9, 0xf3, 0xe7, 0x8f, 0xff,
      0xc3, 0x99, 0xf9, 0xf3, 0xe7, 0xff, 0xe7, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xe7, 0xc3, 0x99, 0x81, 0x99, 0x99, 0x99, 0xff,
      0x83, 0x99, 0x99, 0x83, 0x99, 0x99, 0x83, 0xff,
      0xc3, 0x99, 0x9f, 0x9f, 0x9f, 0x99, 0xc3, 0xff,
      0x87, 0x93, 0x99, 0x99, 0x99, 0x93, 0x87, 0xff,
      0x81, 0x9f, 0x9f, 0x87, 0x9f, 0x9f, 0x81, 0xff,
      0x81, 0x9f, 0x9f, 0x87, 0x9f, 0x9f, 0x9f, 0xff,
      0xc3, 0x99, 0x9f, 0x91, 0x99, 0x99, 0xc3, 0xff,
      0x99, 0x99, 0x99, 0x81, 0x99, 0x99, 0x99, 0xff,
      0xc3, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xc3, 0xff,
      0xe1, 0xf3, 0xf3, 0xf3, 0xf3, 0x93, 0xc7, 0xff,
      0x99, 0x93, 0x87, 0x8f, 0x87, 0x93, 0x99, 0xff,
      0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x81, 0xff,
      0x9c, 0x88, 0x80, 0x94, 0x9c, 0x9c, 0x9c, 0xff,
      0x99, 0x89, 0x81, 0x81, 0x91, 0x99, 0x99, 0xff,
      0xc3, 0x99, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xff,
      0x83, 0x99, 0x99, 0x83, 0x9f, 0x9f, 0x9f, 0xff,
      0xc3, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xf1, 0xff,
      0x83, 0x99, 0x99, 0x83, 0x87, 0x93, 0x99, 0xff,
      0xc3, 0x99, 0x9f, 0xc3, 0xf9, 0x99, 0xc3, 0xff,
      0x81, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff,
      0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xff,
      0x99, 0x99, 0x99, 0x99, 0x99, 0xc3, 0xe7, 0xff,
      0x9c, 0x9c, 0x9c, 0x94, 0x80, 0x88, 0x9c, 0xff,
      0x99, 0x99, 0xc3, 0xe7, 0xc3, 0x99, 0x99, 0xff,
      0x99, 0x99, 0x99, 0xc3, 0xe7, 0xe7, 0xe7, 0xff,
      0x81, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x81, 0xff,
      0xe7, 0xe7, 0xe7, 0x00, 0x00, 0xe7, 0xe7, 0xe7,
      0x3f, 0x3f, 0xcf, 0xcf, 0x3f, 0x3f, 0xcf, 0xcf,
      0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
      0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33,
      0xcc, 0x66, 0x33, 0x99, 0xcc, 0x66, 0x33, 0x99,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
      0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
      0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
      0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
      0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc,
      0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
      0xff, 0xff, 0xff, 0xff, 0x33, 0x33, 0xcc, 0xcc,
      0x33, 0x66, 0xcc, 0x99, 0x33, 0x66, 0xcc, 0x99,
      0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
      0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7,
      0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0,
      0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0x07, 0x07, 0xe7, 0xe7, 0xe7,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
      0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7,
      0xe7, 0xe7, 0xe7, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xe7, 0xe7, 0xe7,
      0xe7, 0xe7, 0xe7, 0x07, 0x07, 0xe7, 0xe7, 0xe7,
      0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
      0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
      0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
      0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
      0xfe, 0xfc, 0xf9, 0x93, 0x87, 0x8f, 0x9f, 0xff,
      0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f,
      0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff,
      0xe7, 0xe7, 0xe7, 0x07, 0x07, 0xff, 0xff, 0xff,
      0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff,
      0x0f, 0x0f, 0x0f, 0x0f, 0xf0, 0xf0, 0xf0, 0xf0,
    };

  const uint8_t *c64_uppercase = c64_font;
  const uint8_t *c64_lowercase = c64_font + 256*8;
#if 1
  if (! strcmp(argv[1], "--dump"))
    {
      printf("C64 uppercase\n");
      fontdump(c64_uppercase);
      printf("\nC64 lowercase\n");
      fontdump(c64_lowercase);
      return 0;
    }
#endif

  for(int i = 1; i < argc; ++i)
    {
      uint8_t *s = reinterpret_cast<uint8_t*>(argv[i]);
      unsigned slen = 0;
      for(unsigned i = 0; s[i]; ++i)
	{
	  ++slen;
	  s[i] = ascii_to_screencode(s[i]);
	}
      print(s, slen, c64_lowercase);
    }
  return 0;
}
