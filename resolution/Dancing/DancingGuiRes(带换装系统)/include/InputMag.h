#ifndef __InputMag_h_
#define __InputMag_h_

class InputMag
{
public:
    InputMag();
    ~InputMag();

    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


};




#endif