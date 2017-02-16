#include "AppDelegate.h"
#include "MainMenuScene.h"

USING_NS_CC;

typedef struct tagResource
{
	cocos2d::Size size;
	char directory[100];
} Resource;

// Landscape config.
// 800x480 = Normal screen, WVGA 
static Resource smallResource = { cocos2d::Size(1000, 550), "sd" };
// 1280x800 = Extra large screen, WXGA, medium density screen (160)
static Resource mediumResource = { cocos2d::Size(1280, 800), "hd" };
// 1900x1200 = WUXGA, Devices with such as Nexus 7, Nvidia Shield.
static Resource largeResource = { cocos2d::Size(1920, 1200), "shd" };

static cocos2d::Size designResolutionSize = smallResource.size;

AppDelegate::AppDelegate() 
{

}

AppDelegate::~AppDelegate() 
{

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
		// Initialize director
		auto director = Director::getInstance();
		auto glview = director->getOpenGLView();
		// Comment out this if statement if testing on an actual device.
		if (!glview) {
			glview = GLViewImpl::create("TBD");
			glview->setFrameSize(designResolutionSize.width, designResolutionSize.height);      
			director->setOpenGLView(glview);
		}

		auto fileUtils = FileUtils::getInstance();

		// Set the design resolution with the NO_BORDER policy.
		glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
		cocos2d::Size frameSize = glview->getFrameSize();
		std::vector<std::string> searchPath;

		// Here, we select the most appropriate resource (i.e. image set) according to the actual frame height of the device.
		// If the resource (image) size is different from design resolution size, we need to set content scale factor.
		// This will either scale the images up or down to match the design resolution size.
		// The content scale factor is the ratio of the resource's height to the height of design resolution.

		// if the frame's height is larger than the height of medium resource size, select large resource.
		float scaleFactor = 1.0f;
		if (frameSize.height > mediumResource.size.height) {
			searchPath.push_back(largeResource.directory);
			scaleFactor = largeResource.size.height / designResolutionSize.height;
		}
		// if the frame's height is larger than the height of small resource size, select medium resource.
		else if (frameSize.height > smallResource.size.height) {
			searchPath.push_back(mediumResource.directory);
			scaleFactor = mediumResource.size.height / designResolutionSize.height;
		}
		// if the frame's height is smaller than the height of medium resource size, select small resource.
		else {
			searchPath.push_back(smallResource.directory);
			scaleFactor = smallResource.size.height / designResolutionSize.height;
		}

		director->setContentScaleFactor(1);
		// Need to add our "data" path too.
		searchPath.push_back("data");
		fileUtils->setSearchPaths(searchPath);

		// Create the GameData singleton.
		m_ptr = GameData::sharedGameData();
		// Create the level loader object to load general game data.
		LevelLoader loader("data/GeneralGameData.json");

		// Set FPS. the default value is 1.0/60 if you don't call this
		director->setAnimationInterval(1.0 / 60);

		// Run
		auto scene = MainMenu::createScene();
		director->runWithScene(scene);

		return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
