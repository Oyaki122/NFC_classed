enum SCENE {
  SELECT,
  PAY,
  READ,
  RESET,
  WRITE,
  NULL_SCENE
}

class SceneFactory {
}

class SceneManager {
 public:
  SceneManager(void) {}
  void setNextScene(SCENE scene) {
    if (scene == NULL_SCENE) return;
    currentScene = SceneFactory::getScene(scene, this);
  };
  void draw(Display* display) {
    if (currentScene == NULL) return;
    currentScene->draw(display);
  };
  void update(NFC* nfc, IInput* input) {
    if (currentScene == NULL) return;
    currentScene->update(nfc, input);
  };

 private:
  unique_ptr<SceneBase> currentScene;
};

class SceneBace {
 public:
  SceneBace(SceneManager* _manager) {
    manager = _manager;
    nfc = _nfc;
    display = _display;
  }
  virtual void update(NFC* nfc, IInput* input) = 0;
  virtual void draw(Display* display) = 0;
  virtual ~SceneBace() {}

 protected:
  setNextScene(SCENE scenes) { manager->setNextScene(scenes); }

 private:
  SceneManager* manager;
};

class PayScene : public SceneBace {
 public:
  virtual void update(NFC* nfc);
  virtual void draw(Display* display, IInput input);

 private:
  bool isError = false;
  char* errorMsg;
};

void PayScene::update(NFC* nfc IInput* input) {
  if (!(nfc.available())) return;
  NFCValue buffer;
  try {
    nfc.read(buffer);
  } catch (char* msg) {
    isError = true;
    errorMsg = msg;
  }
  buffer.credit -= 1;
  try {
    nfc.write(buffer);
  } catch (char* msg) {
    isError = true;
    errorMsg = msg;
  }
}
void PayScene::draw(Display* display) {}