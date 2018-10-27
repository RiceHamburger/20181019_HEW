/*====================================================================================

�I�u�W�F�N�g���N���X�@ [CObject.h]
Autor	: ����
Date	: 2018/09/15
--------------------------------------------------------------------------------------
�R�����g:
--------------------------------------------------------------------------------------
�C������:
====================================================================================*/


#ifndef COBJECT_H
#define COBJECT_H
/*--------------------------------------------------------------------------------------
�C���N���[�h�t�@�C��
--------------------------------------------------------------------------------------*/
#include "primitive2D.h"
//#include "Sprite.h"
#include "Sprite3D.h"
#include "Texture.h"
#include "CObjectMng.h"
/*--------------------------------------------------------------------------------------
�񋓌^ : �\����
--------------------------------------------------------------------------------------*/
typedef enum {

}TextureIndex;



/*--------------------------------------------------------------------------------------
�}�N����`
--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
�N���X�錾
--------------------------------------------------------------------------------------*/
class CObject : public Sprite3D , public CObjectRegister
{
protected:

	//
	//	�I�u�W�F�N�g���
	//
	RectC2D pos;					//�I�u�W�F�N�g���W
	k_Texture m_textureIndex;		//�e�N�X�`���C���f�b�N�X
	bool m_bAlive;					//�����t���O
	//

public:

	//
	//	�����o���\�b�h
	//

	//�R���X�g���N�^ : �f�t�H���g
	CObject();

	//�ǉ��֐�//

	//�Z�b�g : �e�N�X�`���C���f�b�N�X
	void SetTexture(k_Texture index) { m_textureIndex = index; }

	//�X�C�b�`����̐M����M�֐�
	virtual void onSwitch(void) {};

	////////////

};

#endif //COBJECT_H