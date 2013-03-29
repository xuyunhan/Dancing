#ifndef __MovableText_H__
#define __MovableText_H__
#include "Ogre.h"
#include "OgreFont.h"
#include "OgreFontManager.h"
namespace Ogre
{
class MovableText : public MovableObject, public Renderable
{
public:
   /// ˮƽ���뷽ʽ
   enum HorizontalAlignment
   {
    H_LEFT,   ///< �����
    H_CENTER, ///< ����
    H_RIGHT   ///< �Ҷ���
   };
   /// ��ֱ���뷽ʽ
   enum VerticalAlignment
   {
    V_BELOW,///< �Ͷ˶���
    V_ABOVE,///< ���˶���
    V_CENTER///< ����
   };
protected:
   String     mFontName;///<
   String     mType;///<
   String     mName;///<
   DisplayString   mCaption;///< 
   HorizontalAlignment mHorizontalAlignment;///< ˮƽ���뷽ʽ
   VerticalAlignment mVerticalAlignment;///< ��ֱ���뷽ʽ
   ColourValue    mColor;///<
   RenderOperation   mRenderOp;///<
   AxisAlignedBox   mAABB;///<
   LightList    mLList;///<
   Real     mCharHeight;///<
   Real     mSpaceWidth;///<
   bool     mNeedUpdate;///< 
   bool     mUpdateColors;///<
   bool     mOnTop;///<
   Real     mTimeUntilNextToggle;///<
   Real     mRadius;///< ��Χ�뾶
   Real     mAdditionalHeight;///<
   Camera*     mpCam;///< �����ָ��
   RenderWindow*   mpWin;///< ��Ⱦ����ָ��
   FontPtr     mpFont;///< ����ָ��
   MaterialPtr    mpMaterial;///< 
   MaterialPtr    mpBackgroundMaterial;///< ��������
   Vector3     mPositionOffset;///< 
   Vector3     mScaleOffset;///<
public:
   /// ���캯��
   /// @param[in] name ��ʶ��
   /// @param[in] caption ��Ļ�ַ���
   /// @param[in] fontName ������
   /// @param[in] charHeight �ַ��߶�
   /// @param[in] colour �ַ���ɫ
   MovableText(const Ogre::String& name,
    const Ogre::DisplayString& caption,
    const Ogre::String& fontName = "BlueHighway",
    Ogre::Real charHeight = 1.0f,
    const Ogre::ColourValue& colour = Ogre::ColourValue::White);
   virtual ~MovableText(void);
   /// ����������
   void    setFontName(const String &fontName);
   /// ������ʾ��Ļ
   void    setCaption(const DisplayString &caption);
   /// ����������ɫ
   void    setColor(const ColourValue &color);
   /// �������ָ߶�
   void    setCharacterHeight(Real height);
   /// ���ü�����
   void    setSpaceWidth(Real width);
   /// �������ֶ��뷽ʽ
   void    setTextAlignment(const HorizontalAlignment& horizontalAlignment,
    const VerticalAlignment& verticalAlignment);
   /// ����
   void    setAdditionalHeight( Real height );
   /// �Ƿ���ǰ����ʾ
   void    showOnTop(bool show=true);
   /// 
   void setPositionOffset(const Ogre::Vector3& offset);
   /// 
   Ogre::Vector3 getPositionOffset() const { return mPositionOffset; }
   /// 
   void setScaleOffset(const Ogre::Vector3& offset);
   /// 
   Ogre::Vector3 getScaleOffset() const { return mScaleOffset; }
   /// ��ȡ������
   const   String&    getFontName() const {return mFontName;}
   /// ��ȡ��Ļ�ַ���
   const   DisplayString& getCaption() const {return mCaption;}
   /// ��ȡ������ɫ
   const   ColourValue& getColor() const {return mColor;}
   /// ��ȡ�ַ��߶�
   Real    getCharacterHeight() const {return mCharHeight;}
   /// ��ȡ������
   Real    getSpaceWidth() const {return mSpaceWidth;}
   /// 
   Real    getAdditionalHeight() const {return mAdditionalHeight;}
   /// ��ȡ�Ƿ�����ǰ����ʾ
   bool    getShowOnTop() const {return mOnTop;}
   /// ��ȡ��Χ��
   AxisAlignedBox         GetAABB(void) { return mAABB; }
   virtual void visitRenderables(Renderable::Visitor* visitor, bool debugRenderables = false){return;}
protected:
   // from MovableText, create the object
   void _setupGeometry();
   void _updateColors();
   /// ��ȡ��������ϵ�еı任
   void getWorldTransforms(Matrix4 *xform) const;
   /// ��ȡ��Χ�뾶
   Real getBoundingRadius(void) const {return mRadius;};
   /// ��ȡ�����������
   Real getSquaredViewDepth(const Camera *cam) const {return 0;};
   /// ��ȡ��������ϵ�еĳ���
   /// @note һֱ�泯�����
   const   Quaternion&    getWorldOrientation(void) const;
   /// ��ȡ����������ϵ�е�����
   const   Vector3&    getWorldPosition(void) const;
   /// ��ȡ��Χ��
   const   AxisAlignedBox&   getBoundingBox(void) const {return mAABB;};
   /// ��ȡ��ʶ��
   const   String&     getName(void) const {return mName;};
   /// ��ȡ������
   const   String&     getMovableType(void) const {static Ogre::String movType = "MovableText"; return movType;};
   void    _notifyCurrentCamera(Camera *cam);
   void    _updateRenderQueue(RenderQueue* queue);
   // from renderable
   void    getRenderOperation(RenderOperation &op);
   const   MaterialPtr& getMaterial(void) const {assert(!mpMaterial.isNull());return mpMaterial;};
   const   LightList&   getLights(void) const {return mLList;};
};
}
#endif