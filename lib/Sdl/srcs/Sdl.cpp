/*
** EPITECH PROJECT, 2020
** SDL
** File description:
** Sl.cpp
*/

#include "../includes/Sdl.hpp"

sdl::Sdl::Sdl()
{
    _window             =   nullptr; 
    _wdScreenRenderer   =   nullptr;
    _libIsInit          =   false;
    _libIsDestroy       =   false;
    _lifeStr            =   "";
    _scoreStr           =   "";
    _scorePosition      =   {DEFAULT_SCORE_W, DEFAULT_SPRITE_SIZE / 2, DEFAULT_SPRITE_SIZE / 2, DEFAULT_TEXT_H};
    _lifePosition       =   {DEFAULT_LIFE_W, DEFAULT_SPRITE_SIZE / 2, DEFAULT_SPRITE_SIZE / 2, DEFAULT_TEXT_H};

    _spriteSize         =   DEFAULT_SPRITE_SIZE;
    _mapSizeW           =   0;
    _mapSizeH           =   0;
    _PrintBeginX        =   DEFAULT_BEGIN_W;
    _PrintBeginY        =   DEFAULT_BEGIN_H;
    _font               =   nullptr;
    _colorText          =   {0xFF, 0xFF, 0xFF, 0x00};
    _scoreTexture       =   nullptr;
    _lifeTexture        =   nullptr;
    _scoreUpdate        =   false;
    _lifeUpdate         =   false;
    _lastKey            =   -1;

    // Menu part:
    _sidePos            =   0;
    _menuFont           =   nullptr;
    _menuBackground     =   nullptr;
    _menuArrow          =   nullptr;
    _arrowPos           =   {0, 0, 0, 0};
    _MenuOptionTitleTextureArray    =   {nullptr, nullptr, nullptr, nullptr};
    _MenuOptionTitlePositionArray   =   {0};

    _MenuOptionItemsArray           =   {nullptr, nullptr, nullptr, nullptr};
    _MenuOptionItemPositionArray    =   {0};
    _playerName         =   "AAA_";
    _menuDescriptionTextures        =   {nullptr};
    _menuDescriptionPos     = {DEFAULT_SPRITE_SIZE, 0, 0, 0};
    {
        std::vector<InitTab> empty;
        this->init(empty);
        this->menuInit();
    }
}

void sdl::Sdl::_destructor(void)
{
    // Destroy all sprite
    {
        std::map<char, SDL_Texture *>::iterator it = _gameTextureMap.begin();

        while (it != _gameTextureMap.end()) {
            if (it->second) {
                SDL_DestroyTexture(it->second);
            }
            ++it;
        }
    }
    // Destroy Score and life Texture
    if (_scoreTexture) {
        SDL_DestroyTexture(_scoreTexture);
        _scoreTexture = nullptr;
    }
    if (_lifeTexture) {
        SDL_DestroyTexture(_lifeTexture);
        _lifeTexture = nullptr;
    }
    if (_menuBackground) {
        SDL_DestroyTexture(_menuBackground);
        _menuBackground = nullptr;
    }
    if (_menuArrow) {
        SDL_DestroyTexture(_menuArrow);
        _menuArrow = nullptr;
    }
    for (auto &texture : _MenuOptionTitleTextureArray) {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
    for (auto &texture : _MenuOptionItemsArray) {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
    for (auto &texture : _menuDescriptionTextures) {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
    // Destroy fontfont
    if (_font) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
    if (_menuFont) {
        TTF_CloseFont(_menuFont);
        _menuFont = nullptr;
    }
    if (_wdScreenRenderer) {
        SDL_DestroyRenderer(_wdScreenRenderer);
        _wdScreenRenderer = nullptr;
    }
    if (_window) {
        //Destroy window
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    //Quit SDL subsystems
    if (_libIsInit) {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        _libIsInit = false;
    }
    _libIsDestroy = true;
}

sdl::Sdl::~Sdl()
{
    // Destroy all sprite
    {
        std::map<char, SDL_Texture *>::iterator it = _gameTextureMap.begin();

        while (it != _gameTextureMap.end()) {
            if (it->second) {
                SDL_DestroyTexture(it->second);
            }
            ++it;
        }
    }
    // Destroy Score and life Texture
    if (_scoreTexture) {
        SDL_DestroyTexture(_scoreTexture);
    }
    if (_lifeTexture) {
        SDL_DestroyTexture(_lifeTexture);
    }
    if (_menuBackground) {
        SDL_DestroyTexture(_menuBackground);
    }
    if (_menuArrow) {
        SDL_DestroyTexture(_menuArrow);
    }
    for (auto &texture : _MenuOptionTitleTextureArray) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    for (auto &texture : _MenuOptionItemsArray) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    for (auto &texture : _menuDescriptionTextures) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    if (_font) {
        TTF_CloseFont(_font);
    }
    if (_menuFont) {
        TTF_CloseFont(_menuFont);
    }

    if (_wdScreenRenderer) {
        SDL_DestroyRenderer(_wdScreenRenderer);
    }
    if (_window) {
        //Destroy window
        SDL_DestroyWindow(_window);

    }
    //Quit SDL subsystems
    if (_libIsInit) {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

void
sdl::Sdl::resizeDefaultSize(size_t height, size_t width)
{
    if (!_mapSizeW || !_mapSizeH) {
        _spriteSize = DEFAULT_SPRITE_SIZE;
    }
    if (width >= DEFAULT_MAX_SPRITE_W || height >= DEFAULT_MAX_SPRITE_H) {
        if (width > height) {
            _spriteSize = getNewSpriteSize(SCREEN_WIDTH, width);
        } else {
            _spriteSize = getNewSpriteSize(SCREEN_HEIGHT, height);
        }
        _spriteSize = (_spriteSize < 8) ? 8 : _spriteSize;
    }
    _mapSizeH           =   height;
    _mapSizeW           =   width;
    _PrintBeginX        =   DEFAULT_SCREEN_CENTER_W - (_spriteSize * width / 2);
    _PrintBeginY        =   DEFAULT_SCREEN_CENTER_H - (_spriteSize * height / 2);
    _scorePosition      =   {//static_cast<int>(_spriteSize),
                            static_cast<int>(_PrintBeginX),
                            static_cast<int>(_PrintBeginY / 2 - _spriteSize / 2),
                            _scorePosition.w,
                            _scorePosition.h};
    _lifePosition       =   {/*DEFAULT_SCREEN_CENTER_W + static_cast<int>*/(_spriteSize * width),
                            // static_cast<int>(_spriteSize) / 2,
                            static_cast<int>(_PrintBeginY / 2 - _spriteSize / 2),
                            _lifePosition.w,
                            _lifePosition.h};
}

void
sdl::Sdl::displayGame(const std::vector<std::vector<char>> &arr)
{
    SDL_Texture *tmp        = nullptr;
    SDL_Rect    sptPosition = {0, 0, DEFAULT_BEGIN_W, DEFAULT_BEGIN_H};

    if (!_window) {
        if (_libIsDestroy)
            _destructor();
        return;
    }

    SDL_RenderClear(_wdScreenRenderer);

    if (arr.size() != this->_mapSizeH || arr[0].size() != this->_mapSizeW) {
       resizeDefaultSize(arr.size(), arr.size() ? arr.front().size() : 0);
    }

    for (size_t yIdx = 0, yEnd = arr.size(); yIdx < yEnd; ++yIdx) {
        for (size_t xIdx = 0, xEnd = arr.at(yIdx).size(); xIdx < xEnd; ++xIdx) {
            if (this->_gameTextureMap.find(arr[yIdx][xIdx]) != this->_gameTextureMap.end()) {
                tmp = this->_gameTextureMap[arr[yIdx][xIdx]];
                if (tmp) {
                    sptPosition.h = this->_spriteSize;
                    sptPosition.w = this->_spriteSize;
                    sptPosition.x = _PrintBeginX + xIdx * this->_spriteSize;
                    sptPosition.y = _PrintBeginY + yIdx * this->_spriteSize;
                    SDL_RenderCopy(_wdScreenRenderer, tmp, NULL, &sptPosition);
                }
            }
        }
    }

    if (_scoreUpdate) {
        std::string s = "Score : " + _scoreStr;
        if (_scoreTexture) {
            SDL_DestroyTexture(_scoreTexture);
        }
        _scoreTexture = _createText(s, _scorePosition, _font, _colorText);
        _scoreUpdate = false;
    }
    if (_lifeUpdate) {
        std::string s = "Life : " + _lifeStr;
        if (_lifeTexture) {
            SDL_DestroyTexture(_lifeTexture);
        }
        _lifeTexture = _createText(s, _lifePosition, _font, _colorText);
        _lifePosition.x = _PrintBeginX + (_mapSizeW * _spriteSize) - _lifePosition.w;
        _lifeUpdate = false;
    }
    if (_scoreTexture) {
        SDL_RenderCopy(_wdScreenRenderer, _scoreTexture, NULL, &_scorePosition);
    }
    if (_lifeTexture) {
        SDL_RenderCopy(_wdScreenRenderer, _lifeTexture, NULL, &_lifePosition);
    }

    SDL_RenderPresent(_wdScreenRenderer);
}

void
sdl::Sdl::setPreview(std::vector<std::vector<char>> &arr)
{
}

std::string
sdl::Sdl::getName()
{
    return _playerName;
}



void sdl::Sdl::init(const std::vector<InitTab> &arr)
{
    if (_libIsInit == false) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            return;
        }
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            return;
        }
        //Create window
        _window = SDL_CreateWindow(
            "Arcade",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );
        if (!_window) {
            return;
        }

        _wdScreenRenderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (!_wdScreenRenderer) {
            return;
        }
        SDL_SetRenderDrawColor(_wdScreenRenderer, 0x00, 0x00, 0x00, 0x00);

        if ( !(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
            return;
        }

        if (TTF_Init() == -1) {;
        }
        _font = TTF_OpenFont("lib/Sdl/assets/BohemianTypewriter.ttf", DEFAULT_POLICE_SIZE);

        _libIsInit = true;
    }
    if (arr.size())
    {
        SDL_Surface *loadedSurface = nullptr;

        for (const InitTab &obj : arr) {
            loadedSurface = IMG_Load(obj.getPath().c_str());
            if (loadedSurface) {
                _gameTextureMap[obj.getCharacter()] = SDL_CreateTextureFromSurface(_wdScreenRenderer, loadedSurface);
                SDL_FreeSurface(loadedSurface);
            } else {
                _gameTextureMap[obj.getCharacter()] = nullptr;
            }
            // if load failed, the sprite will not be printed
        }
    }
}

SDL_Texture *
sdl::Sdl::_createText(const std::string &str, SDL_Rect &rec, TTF_Font *font, SDL_Color &color)
{
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_Texture *texture = nullptr;

    if (surfaceText) {
        texture = SDL_CreateTextureFromSurface(_wdScreenRenderer, surfaceText);
        if (!texture) {
            return nullptr;
        }
        rec.w = surfaceText->w;
        rec.h = surfaceText->h;
        SDL_FreeSurface(surfaceText);
    } else {
        return nullptr;
    }
    return texture;
}

SDL_Texture *
sdl::Sdl::_createText(const char *str, SDL_Rect &rec, TTF_Font *font, SDL_Color &color)
{
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, str, color);
    SDL_Texture *texture = nullptr;

    if (surfaceText) {
        texture = SDL_CreateTextureFromSurface(_wdScreenRenderer, surfaceText);
        if (!texture) {
            return nullptr;
        }
        rec.w = surfaceText->w;
        rec.h = surfaceText->h;
        SDL_FreeSurface(surfaceText);
    } else {
        return nullptr;
    }
    return texture;
}

void
sdl::Sdl::setScore(const std::string &score)
{
    if (_scoreStr != score) {
        _scoreUpdate = true;
        this->_scoreStr = score;
    }
    //  else {
        // _scoreUpdate = false;
    // }
}

void
sdl::Sdl::setLife(const std::string &life)
{
    if (_lifeStr != life) {
        _lifeUpdate = true;
        this->_lifeStr = life;
    }
    //  else {
        // _lifeUpdate = false;
    // }
}

Input
sdl::Sdl::getInput(void)
{
    Input key = NONE;

    if (!_window) {
        return EXIT;
    }
    while (SDL_PollEvent(&_event)) {
        if (this->_event.type == SDL_QUIT) {
            return EXIT;
        }
        if (_event.key.type == SDL_KEYDOWN) {
            _lastKey = _event.key.keysym.sym;
            switch (_lastKey)
            {
            case SDLK_UP:
                key = UP;
                break;
            case SDLK_DOWN:
                key = DOWN;
                break;
            case SDLK_LEFT:
                key = LEFT;
                break;
            case SDLK_RIGHT:
                key = RIGHT;
                break;
            case SDLK_ESCAPE:
                key = EXIT;
                break;
            case SDLK_a:
            case 'A':
                key = PREV_GAME;
                break;
            case SDLK_e:
            case 'E':
                key = NEXT_GAME;
                break;
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                key = ENTER;
                break;
            case SDLK_w:
            case 'W':
                key = PREV_GRAPH;
                break;
            case SDLK_c:
            case 'C':
                key = NEXT_GRAPH;
                break;
            default:
                key = NONE;
                break;
            }
        }
    }
    return key;
}

void
sdl::Sdl::displayMenu(const Info &info)
{   
    if (!_window) {
        if (_libIsDestroy)
            _destructor();
        return;
    }
    SDL_RenderClear(_wdScreenRenderer);

    _sidePos = info.getSide();
    if (_sidePos == NAME_IDX && _lastKey != -1 && _lastKey != SDLK_LEFT && _lastKey != SDLK_RIGHT) {
        if (_lastKey == SDLK_BACKSPACE && _playerName.length()) {
            _playerName.pop_back();
        } else if (_playerName.size() < 12 && std::isalnum(static_cast<unsigned char>(_lastKey))) {
            _playerName += ::std::toupper(static_cast<unsigned char>(_lastKey));
        }
        _lastKey = -1;
    }

    {
        if (_menuBackground) {
            SDL_RenderCopy(_wdScreenRenderer, _menuBackground, nullptr, nullptr);
        }
    }

    {
        size_t backupY = _menuDescriptionPos.y;
        for (size_t idx = 0, end = _menuDescriptionTextures.size(); idx < end; ++idx) {
            if (_menuDescriptionTextures.at(idx)) {
                _menuDescriptionPos.y = backupY + (idx * _menuDescriptionPos.h);
                SDL_RenderCopy(_wdScreenRenderer, _menuDescriptionTextures.at(idx), NULL, &_menuDescriptionPos);
            }
        }
        _menuDescriptionPos.y = backupY;
    }

    for (size_t idx = 0; idx < 4; ++idx) {
        if (_MenuOptionTitleTextureArray[idx])
            SDL_RenderCopy(_wdScreenRenderer, _MenuOptionTitleTextureArray[idx], nullptr, &_MenuOptionTitlePositionArray[idx]);
    }
    _displaySelectedLib(info);
    _displaySelectedGame(info);
    _displayPlayerName();
    _displayScore(info);
    if (_menuArrow) {
        _arrowPos.y = _MenuOptionTitlePositionArray[_sidePos].y - _arrowPos.h / 2;
        SDL_RenderCopy(_wdScreenRenderer, _menuArrow, nullptr, &_arrowPos);
    }
    SDL_RenderPresent(_wdScreenRenderer);

}

void
sdl::Sdl::_displaySelectedLib(const Info &info)
{
    _MenuOptionItemsArray[LIB_IDX] = _createText(info.getGraphNames().at(info.getGraphIdx()), _MenuOptionItemPositionArray[LIB_IDX], _menuFont,_colorText);
    _MenuOptionItemPositionArray[LIB_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionItemPositionArray[LIB_IDX].w / 2;

    if (_MenuOptionItemsArray[LIB_IDX]) {
        SDL_RenderCopy(_wdScreenRenderer, _MenuOptionItemsArray[LIB_IDX], NULL, &_MenuOptionItemPositionArray[LIB_IDX]);
    }
}

void
sdl::Sdl::_displaySelectedGame(const Info &info)
{
    _MenuOptionItemsArray[GAME_IDX] = _createText(info.getGameNames().at(info.getGameIdx()), _MenuOptionItemPositionArray[GAME_IDX], _menuFont, _colorText);
    _MenuOptionItemPositionArray[GAME_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionItemPositionArray[GAME_IDX].w / 2;

    if (_MenuOptionItemsArray[GAME_IDX]) {
        SDL_RenderCopy(_wdScreenRenderer, _MenuOptionItemsArray[GAME_IDX], NULL, &_MenuOptionItemPositionArray[GAME_IDX]);
    }
}

void
sdl::Sdl::_displayPlayerName(void)
{
    _MenuOptionItemsArray[NAME_IDX] = _createText(_playerName, _MenuOptionItemPositionArray[NAME_IDX], _menuFont, _colorText);
    _MenuOptionItemPositionArray[NAME_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionItemPositionArray[NAME_IDX].w / 2;

    if (_MenuOptionItemsArray[NAME_IDX]) {
        SDL_RenderCopy(_wdScreenRenderer, _MenuOptionItemsArray[NAME_IDX], NULL, &_MenuOptionItemPositionArray[NAME_IDX]);
    }
}

void concatAndSortScore(const std::vector<Score> &sc, std::vector<std::string> &res)
{
    res.clear();
    for (size_t idx =0; idx < sc.size(); ++idx) {
        res.push_back(std::string(sc[idx].getScore() + " " + sc[idx].getName()));
    }
}

void
sdl::Sdl::_displayScore(const Info &info)
{
    const std::vector<Score> &  score = info.getScoring();

    if (_score_with_name.size() != score.size()) {
        concatAndSortScore(score, _score_with_name);
    }
    for (size_t idx = 0; idx < _score_with_name.size(); ++idx) {

        if (_MenuOptionItemsArray[SCORE_IDX]) {
            SDL_DestroyTexture(_MenuOptionItemsArray[SCORE_IDX]);
        }
        _MenuOptionItemsArray[SCORE_IDX] = _createText(_score_with_name.at(idx), _MenuOptionItemPositionArray[SCORE_IDX], _menuFont, _colorText);
        _MenuOptionItemPositionArray[SCORE_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionItemPositionArray[SCORE_IDX].w / 2;
        _MenuOptionItemPositionArray[SCORE_IDX].y = _MenuOptionTitlePositionArray[SCORE_IDX].y + _spriteSize + idx * _MenuOptionItemPositionArray[SCORE_IDX].h;

        if (_MenuOptionItemsArray[SCORE_IDX]) {
            SDL_RenderCopy(_wdScreenRenderer, _MenuOptionItemsArray[SCORE_IDX], NULL, &_MenuOptionItemPositionArray[SCORE_IDX]);
        }
    }
}


SDL_Texture *
sdl::Sdl::_createTexture(std::string path)
{
    SDL_Surface *loadedSurface = nullptr;
    SDL_Texture *texture = nullptr;

    loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface) {
        texture = SDL_CreateTextureFromSurface(_wdScreenRenderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}

void
sdl::Sdl::menuInit(void)
{
    
    _menuBackground = _createTexture(MENU_BACKGROUND_PATH);
    _menuArrow      = _createTexture(MENU_ARROW_PATH);
    _menuFont       = TTF_OpenFont(MENU_FONT_PATH, DEFAULT_POLICE_MENU_SIZE);
    SDL_Color descriptionColorText  = {0x03, 0xe1, 0xfc, 0x00};//03c1fc // aaaa00
    std::string keyDescription[]   =   {
        {"LEFT and RIGHT arrow to navigate and move."},
        {"UP and DOWN arrow to change option."},
        {"'A' and 'E' to change the game in game."},
        {"'W' and 'C' to change the library in game."},
        {"ENTER key to launch or reset the game."},
        {"ESCAPE to quit or come back to the menu."}
    };
    for (auto &line : keyDescription) {
        _menuDescriptionTextures.push_back(_createText(line, _menuDescriptionPos, _menuFont, descriptionColorText));
    }
    _menuDescriptionPos.w /= 1.5;
    _menuDescriptionPos.h /= 1.5;
    _menuDescriptionPos.y = SCREEN_HEIGHT - (_menuDescriptionPos.h * 7) - _spriteSize;

    if (!_menuFont) {
        // throw err
    }
    _MenuOptionTitleTextureArray[GAME_IDX] = _createText("Libraries :", _MenuOptionTitlePositionArray[GAME_IDX], _font, _colorText);
    _MenuOptionTitlePositionArray[GAME_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionTitlePositionArray[GAME_IDX].w / 2;
    _MenuOptionTitlePositionArray[GAME_IDX].y = 3 * DEFAULT_BEGIN_H + 0 * _MenuOptionTitlePositionArray[GAME_IDX].h * 3;

    _MenuOptionTitleTextureArray[LIB_IDX] = _createText("Games :", _MenuOptionTitlePositionArray[LIB_IDX], _font, _colorText);
    _MenuOptionTitlePositionArray[LIB_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionTitlePositionArray[LIB_IDX].w / 2;
    _MenuOptionTitlePositionArray[LIB_IDX].y = 3 * DEFAULT_BEGIN_H + 1 * _MenuOptionTitlePositionArray[1].h * 3;

    _MenuOptionTitleTextureArray[NAME_IDX] = _createText("Player Name :", _MenuOptionTitlePositionArray[NAME_IDX], _font, _colorText);
    _MenuOptionTitlePositionArray[NAME_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionTitlePositionArray[NAME_IDX].w / 2;
    _MenuOptionTitlePositionArray[NAME_IDX].y = 3 * DEFAULT_BEGIN_H + 2 * _MenuOptionTitlePositionArray[NAME_IDX].h * 3;

    _MenuOptionTitleTextureArray[SCORE_IDX] = _createText("High Score :", _MenuOptionTitlePositionArray[SCORE_IDX], _font, _colorText);
    _MenuOptionTitlePositionArray[SCORE_IDX].x = DEFAULT_SCREEN_CENTER_W - _MenuOptionTitlePositionArray[SCORE_IDX].w / 2;
    _MenuOptionTitlePositionArray[SCORE_IDX].y = 3 * DEFAULT_BEGIN_H + 3 * _MenuOptionTitlePositionArray[SCORE_IDX].h * 3;

    _arrowPos.x = _MenuOptionTitlePositionArray[GAME_IDX].x - 3 * _spriteSize;
    _arrowPos.y = _MenuOptionTitlePositionArray[GAME_IDX].y;
    _arrowPos.w = _spriteSize * 2;
    _arrowPos.h = _spriteSize * 2;

    _MenuOptionItemPositionArray[GAME_IDX].y = _MenuOptionTitlePositionArray[GAME_IDX].y + _spriteSize;
    _MenuOptionItemPositionArray[LIB_IDX].y = _MenuOptionTitlePositionArray[LIB_IDX].y + _spriteSize;
    _MenuOptionItemPositionArray[NAME_IDX].y = _MenuOptionTitlePositionArray[NAME_IDX].y + _spriteSize;
    _MenuOptionItemPositionArray[SCORE_IDX].y = _MenuOptionTitlePositionArray[SCORE_IDX].y + _spriteSize;
}

extern "C"
{
    std::shared_ptr<IGraphics>
    createInterface(void)
    {
        return std::make_shared<sdl::Sdl>();
    }
}
