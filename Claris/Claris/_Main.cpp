/*
	zd ... zero disabled

	float, double ���[���N���A�����l�E�L��ϐ��̏����l�� 0.0 �Ƃ���B
	float, double �̌v�Z���ʂ͊��ɂ���Č덷��������̂Ƃ���B

	----
	�Q�[�����[�v�̊�{�`

//	ActFrame = 0; // �K�v�Ȃ��
	FreezeInput();

	for(; ; )
	{
		1. ����
			���[�v�̒E�o
			���荞�ݏ���
				���E�����E�ē������͂����ōs���H
				FreezeInput();
		2. �`��
		3. EachFrame();
	}
//	FreezeInput(); // �O�̂���
*/

#include "all.h"

void ProcMain(void)
{
#if !LOG_ENABLED // product
	Logo();
	MainMenu();
#elif 0 // test
	{
		GameInit();
		GDc.MapFile = strx("..\\..\\map\\0001.bmp");
		GameMain();
		GameFnlz();
	}
#elif 0 // test
	MainMenu();
#else // test
	Logo();
	MainMenu();
#endif
}
