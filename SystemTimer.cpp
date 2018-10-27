//=====================================================================//
//		�V�X�e���^�C�}�[ [systemTimer.cpp]                             //
//                                                                     //
//                                               GP51A247 SoSei        //
//                                               2018/06/15            //
//---------------------------------------------------------------------//
//                                                                     //
//=====================================================================//
#include "SystemTimer.h"

//=====================================================================//
//                                                                     //
//							�O���[�o���ϐ��錾	                       //
//                                                                     //
//=====================================================================//
static bool g_bTimerStopped = true; // �X�g�b�v�t���O
static LONGLONG g_TicksPerSec = 0;  // �P�b�Ԃ̌v������
static LONGLONG g_StopTime;         // �X�g�b�v��������
static LONGLONG g_LastElapsedTime;  // �Ō�ɋL�^�����X�V����
static LONGLONG g_BaseTime;         // ��{����

/* --------------------------------
��~���Ă���Β�~���ԁA�����łȂ���Ό��݂̎��Ԃ̎擾
-------------------------------- */
static LARGE_INTEGER GetAdjustedCurrentTime(void);


//=====================================================================//
//                                                                     //
//						�V�X�e���^�C�}�[�̏�����					   //
//                                                                     //
//=====================================================================//
void SystemTimerInitialize(void)
{
	/* --------------------------------
	�ϐ�������
	-------------------------------- */
    g_bTimerStopped = true;
    g_TicksPerSec = 0;
    g_StopTime = 0;
    g_LastElapsedTime = 0;
    g_BaseTime = 0;

	/* --------------------------------
	������\�p�t�H�[�}���X�J�E���^���g���̎擾
	-------------------------------- */
    LARGE_INTEGER ticksPerSec = { 0 };
    QueryPerformanceFrequency(&ticksPerSec);
    g_TicksPerSec = ticksPerSec.QuadPart;
}
//=====================================================================//
//                                                                     //
//						�V�X�e���^�C�}�[�̃��Z�b�g					   //
//                                                                     //
//=====================================================================//
void SystemTimerReset(void)
{
	/* --------------------------------
	�^�C�}�[���Z�b�g
	-------------------------------- */
    LARGE_INTEGER time = GetAdjustedCurrentTime();

    g_BaseTime = g_LastElapsedTime = time.QuadPart;
    g_StopTime = 0;
    g_bTimerStopped = false;
}
//=====================================================================//
//                                                                     //
//						�V�X�e���^�C�}�[�̃X�^�[�g					   //
//                                                                     //
//=====================================================================//
void SystemTimerStart(void)
{
	/* --------------------------------
	���݂̎��Ԃ��擾
	-------------------------------- */
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);
	/* --------------------------------
	���܂Ōv�����X�g�b�v���Ă�����
	-------------------------------- */
    if( g_bTimerStopped ) 
	{
		/* --------------------------------
		�~�܂��Ă������Ԃ����������Ċ�{���Ԃ��X�V
		-------------------------------- */
        g_BaseTime += time.QuadPart - g_StopTime;
    }
	/* --------------------------------
	���Z�b�g�ݒ�
	-------------------------------- */
    g_StopTime = 0;
    g_LastElapsedTime = time.QuadPart;
    g_bTimerStopped = false;
}
//=====================================================================//
//                                                                     //
//						�V�X�e���^�C�}�[�̃X�g�b�v					   //
//                                                                     //
//=====================================================================//
void SystemTimerStop(void)
{
	/* --------------------------------
	�^�C�}�[����~������
	-------------------------------- */
    if( g_bTimerStopped ) return;

	/* --------------------------------
	���Z�b�g�ݒ�
	-------------------------------- */
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);
	/* --------------------------------
	��~���Ԃ��L�^
	-------------------------------- */
    g_LastElapsedTime = g_StopTime = time.QuadPart;
    g_bTimerStopped = true;
}

//=====================================================================//
//                                                                     //
//						�V�X�e���^�C�}�[��0.1�b�i					   //
//                                                                     //
//=====================================================================//
void SystemTimerAdvance(void)
{	
	/* --------------------------------
	�V�X�e���^�C�}�[��0.1�b�i�߂�
	-------------------------------- */
    g_StopTime += g_TicksPerSec / 10;
}
//=====================================================================//
//                                                                     //
//						�Q�b�g�V�X�e���^�C�}�[						   //
//                                                                     //
//=====================================================================//
double SystemTimerGetTime(void)
{
	/* --------------------------------
	�Q�b�g����
	-------------------------------- */
    LARGE_INTEGER time = GetAdjustedCurrentTime();
	/* --------------------------------
	�v�����Ԃ����^�[��
	-------------------------------- */
    return (double)(time.QuadPart - g_BaseTime) / (double)g_TicksPerSec;
}
//=====================================================================//
//                                                                     //
//						�Q�b�g�V�X�e�����ݎ���						   //
//                                                                     //
//=====================================================================//
double SystemTimerGetAbsoluteTime(void)
{
	/* --------------------------------
	�^�C�}�[���Z�b�g
	-------------------------------- */
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);
	/* --------------------------------
	���^�[���V�X�e�����ݎ���
	-------------------------------- */
    return time.QuadPart / (double)g_TicksPerSec;
}
//=====================================================================//
//                                                                     //
//						�Q�b�g�V�X�e���o�ߎ���						   //
//                                                                     //
//=====================================================================//
float SystemTimerGetElapsedTime(void)
{
	/* --------------------------------
	�^�C�}�[���Z�b�g 
	�v�Z
	-------------------------------- */
    LARGE_INTEGER time = GetAdjustedCurrentTime();

    double elapsed_time = (float)((double)(time.QuadPart - g_LastElapsedTime) / (double)g_TicksPerSec);
    g_LastElapsedTime = time.QuadPart;

    // �^�C�}�[�����m�ł��邱�Ƃ�ۏ؂��邽�߂ɁA�X�V���Ԃ��O�ɃN�����v����B
    // elapsed_time�́A�v���Z�b�T���ߓd���[�h�ɓ��邩�A���炩�̌`�ŕʂ̃v���Z�b�T�ɃV���b�t�������ƁA���͈̔͊O�ɂȂ�\��������B
    // ����āA���C���X���b�h��SetThreadAffinityMask���Ăяo���āA�ʂ̃v���Z�b�T�ɃV���b�t������Ȃ��悤�ɂ���K�v������B
    // ���̃��[�J�[�X���b�h��SetThreadAffinityMask���Ăяo���ׂ��ł͂Ȃ��A���C���X���b�h������W���ꂽ�^�C�}�[�f�[�^�̋��L�R�s�[���g�p���邱�ƁB
    if( elapsed_time < 0.0f ) {
        elapsed_time = 0.0f;
    }
	/* --------------------------------
	���^�[���o�ߎ���
	-------------------------------- */
    return (float)elapsed_time;
}

//=====================================================================//
//                                                                     //
//					�V�X�e���^�C�}�[��ԃ`�F�b�N					   //
//                                                                     //
//=====================================================================//
bool SystemTimerIsStoped(void)
{
	/* --------------------------------
	�V�X�e���^�C�}�[���~�܂��Ă��邩�H
	-------------------------------- */
    return g_bTimerStopped;
}
//=====================================================================//
//                                                                     //
//						�v���Z�b�T�̐����֐�						   //
//                                                                     //
//=====================================================================//
void LimitThreadAffinityToCurrentProc(void)
{
	/* --------------------------------
	���݂̃X���b�h��1�̃v���Z�b�T�i���݂̃X���b�h�j�ɐ���
	-------------------------------- */
    HANDLE hCurrentProcess = GetCurrentProcess();

    // Get the processor affinity mask for this process
    DWORD_PTR dwProcessAffinityMask = 0;
    DWORD_PTR dwSystemAffinityMask = 0;

    if( GetProcessAffinityMask(hCurrentProcess, &dwProcessAffinityMask, &dwSystemAffinityMask) != 0 && dwProcessAffinityMask ) {
        // Find the lowest processor that our process is allows to run against
        DWORD_PTR dwAffinityMask = (dwProcessAffinityMask & ((~dwProcessAffinityMask) + 1));

        // Set this as the processor that our thread must always run against
        // This must be a subset of the process affinity mask
        HANDLE hCurrentThread = GetCurrentThread();
        if( INVALID_HANDLE_VALUE != hCurrentThread ) {
            SetThreadAffinityMask(hCurrentThread, dwAffinityMask);
            CloseHandle(hCurrentThread);
        }
    }
	/* --------------------------------
	�n���h�����I��
	-------------------------------- */
    CloseHandle(hCurrentProcess);
}
//=====================================================================//
//                                                                     //
//						���݂̎��Ԃ̎擾�֐�						   //
//                                                                     //
//=====================================================================//
LARGE_INTEGER GetAdjustedCurrentTime(void)
{
	/* --------------------------------
	��~���Ă���Β�~���ԁA�����łȂ���Ό��݂̎��Ԃ̎擾
	-------------------------------- */
    LARGE_INTEGER time;
	/* --------------------------------
	��~���Ă��Ȃ�
	-------------------------------- */
    if( g_StopTime != 0 ) 
	{
        time.QuadPart = g_StopTime;
    }
	/* --------------------------------
	��~���Ă���
	-------------------------------- */
    else 
	{
        QueryPerformanceCounter(&time);
    }
	/* --------------------------------
	���Ԃ����^�[��
	-------------------------------- */
    return time;
}
