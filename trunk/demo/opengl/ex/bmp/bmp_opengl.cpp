#include "resource.h"

#include <windows.h>
#include <tchar.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "ugldialog.h"
#include "udlgapp.h"
#include "uglut.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//                                        BMP TEXTURE LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////
void BMP_Texture(UINT textureArray[], LPSTR sFileName, int ID)
{
    if(!sFileName)   return;

    HBITMAP hBMP;                                                        // Handle Of The Bitmap
    BITMAP    bmp;

    hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), sFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

    if (!hBMP)                                                            // Does The Bitmap Exist?
        return;

    ::GetObject(hBMP, sizeof(bmp), &bmp);


    glGenTextures(1, &textureArray[ID]);
    glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_RGB, GL_UNSIGNED_BYTE, bmp.bmBits);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    DeleteObject(hBMP);                                                    // Delete The Object
}

using huys::UGLDialog;


class MyGLDialog : public UGLDialog
{
    UINT TextureArray[1];
public:
    MyGLDialog(HINSTANCE hInst, UINT nID)
    : UGLDialog(hInst, nID)
    {
    }

    BOOL initGL()
    {
        RECT rc;
        ::GetClientRect(m_hDlg, &rc);
        UGlut::ResizeScene(rc.right-rc.left, rc.bottom-rc.top);

        glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                // Black Background
        glClearDepth(1.0f);                                    // Depth Buffer Setup
        glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
        glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations

        glEnable(GL_TEXTURE_2D);

        BMP_Texture(TextureArray, "texture.bmp", 0);

        return TRUE;
    }

    virtual BOOL animate()
    {
        // Clear Screen And Depth Buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Reset The Current Modelview Matrix
        glLoadIdentity();

        glTranslatef(0, 0,-5.0f);

    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);

    glBegin(GL_QUADS);
        // top left vertex
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1, 1, 0);
        // bottom left vertex
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1, -1, 0);
        // bottom right vertex
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1, -1, 0);
        // top right vertex
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1, 1, 0);
    glEnd();

        return TRUE;
    }

    virtual BOOL onChar(WPARAM wParam, LPARAM lParam)
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            return UGLDialog::onCancel();
        default:
            return UGLDialog::onChar(wParam, lParam);
        }
    }

};

UDLGAPP_T(MyGLDialog, IDD_TEST);
