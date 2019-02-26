#pragma once

#include<windows.h>        /**< ����windows.h�ļ� */

#define BITMAP_ID 0x4D42    /**< λͼ�ļ��ı�־ */

/** λͼ������ */
class CBMPLoader
{
   public:
      CBMPLoader();
      ~CBMPLoader();

      bool LoadBitmap(char *filename); /**< װ��һ��bmp�ļ� */
      void FreeImage();                /**< �ͷ�ͼ������ */

      unsigned int ID;                 /**< ���������ID�� */
      int imageWidth;                  /**< ͼ���� */
      int imageHeight;                 /**< ͼ��߶� */
      unsigned char *image;            /**< ָ��ͼ�����ݵ�ָ�� */
};

