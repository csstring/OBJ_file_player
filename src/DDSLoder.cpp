#include "DDSLoder.h"
#include "GL/glew.h"

uint32 DDSLoder::loadDDS(void)
{
  unsigned char header[124];

  FILE *fp;

  fp = fopen(_imagepath.c_str(), "rb");
  if (fp == NULL)
    return 0;

    /* 파일 타입 체크 */
  char filecode[4];
  fread(filecode, 1, 4, fp);
  if (strncmp(filecode, "DDS ", 4) != 0) {
      fclose(fp);
      return 0;
  }

  fread(&header, 124, 1, fp);

  height = *(unsigned int*)&(header[8]);
  width = *(unsigned int*)&(header[12]);
  linearSize = *(unsigned int*)&(header[16]);
  mipMapCount = *(unsigned int*)&(header[24]);
  fourCC = *(unsigned int*)&(header[80]);

  unsigned int bufsize;

  bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
  buffer = new unsigned char[bufsize*sizeof(unsigned char)];
  fread(buffer, 1, bufsize, fp);

  fclose(fp);

  unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
  switch(fourCC)
  {
  case FOURCC_DXT1:
      format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
  case FOURCC_DXT3:
      format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
  case FOURCC_DXT5:
      format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
  default:
      return 0;
  }

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
  unsigned int offset = 0;

    /* load the mipmaps */
  for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
  {
      unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
      glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
            0, size, buffer + offset);

      offset += size;
      width  /= 2;
      height /= 2;
  }

  return textureID;
}