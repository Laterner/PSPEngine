#include <oslib/oslib.h>
#include <psputils.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspmpeg.h>

PSP_MODULE_INFO("Hello World", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

// Init OSLib:
void initOSLib(){
    oslInit(0);
    oslInitGfx(_16bit, 1);
    oslInitAudio();
    oslSetDrawBuffer(OSL_DEFAULT_BUFFER);
    oslSetQuitOnLoadFailure(1);
    oslSetKeyAutorepeatInit(40);
    oslSetKeyAutorepeatInterval(10);
    return 0;
}


// Main:
int main(){
    int skip = 0;

    initOSLib();
    oslIntraFontInit(INTRAFONT_CACHE_MED);

    //Loads image:
    OSL_IMAGE *bkg = oslLoadImageFilePNG("./gfx/bg.png",OSL_IN_RAM, OSL_PF_5551);
    // OSL_IMAGE *bkg = oslLoadImageFilePNG("./bkg.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

    //Load font:
    OSL_FONT *pgfFont = oslLoadFontFile("flash0:/font/ltn0.pgf");
    oslIntraFontSetStyle(pgfFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
    oslSetFont(pgfFont);

    while(!osl_quit){
        if (!skip){
            oslStartDrawing();

            oslDrawImageXY(bkg, 0, 0);
            oslDrawString(180, 150, "Hello world");
            oslDrawString(150, 250, "Press X to quit");

            oslEndDrawing();
        }
        oslEndFrame();
        skip = oslSyncFrame();

        oslReadKeys();
        if (osl_keys->released.cross)
            oslQuit();
    }
    //Quit OSL:
    oslEndGfx();

    sceKernelExitGame();
    return 0;

}
