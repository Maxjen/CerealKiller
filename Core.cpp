/*
    Copyright (c) 2012 Max Jensen <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Core.h"

namespace ck {

void Core::sdldie(const char *msg) {
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void Core::checkSDLError(int line) {
#ifndef NDEBUG
        const char *error = SDL_GetError();
        if (*error != '\0')
        {
                printf("SDL Error: %s\n", error);
                if (line != -1)
                        printf(" + line: %i\n", line);
                SDL_ClearError();
        }
#endif
}

Core::Core(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize SDL's Video subsystem
        sdldie("Unable to initialize SDL"); // Or die on error

    // Request opengl 3.2 context.
    // SDL doesn't have the ability to choose which profile at this time of writing,
    // but it should default to the core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create our window centered at 512x512 resolution
    mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow) // Die if creation failed
        sdldie("Unable to create window");

    checkSDLError(__LINE__);

    // Create our opengl context and attach it to our window
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);


    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    //printf("Initializing glew\n");
    GLenum status = glewInit();
    if(status != GLEW_OK) {
        fprintf(stderr, "INFO: glew couldn't be initialized. Exit\nGLEW Error: %s", glewGetErrorString(status));
        close();
    }

    actionHandler = nullptr;

    resourceManager = new ResourceManager();
    renderManager = new RenderManager(resourceManager);

    triangles = new Triangles(renderManager);

    selection = new Selection(renderManager, triangles);
    glPointSize(3.0f);

    selectionLayer = new Layer(renderManager);

    glViewport(0, 0, screenWidth, screenHeight);

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE); // enabled by default
    glDepthFunc(GL_LEQUAL);

    setupWorld();
}

void Core::setupWorld() {
    int v1 = triangles->addVertex(500.0f, 200.0f, 0.0f, 1.0f, 255, 0, 255, 255);
    int v2 = triangles->addVertex(500.0f, 400.0f, 0.0f, 0.0f, 0, 255, 255, 255);
    int v3 = triangles->addVertex(700.0f, 400.0f, 1.0f, 0.0f, 0, 255, 255, 255);
    int v4 = triangles->addVertex(700.0f, 200.0f, 1.0f, 1.0f, 0, 0, 255, 255);
    triangles->addTriangle(v1, v2, v3, "Textures/Canyon.png");
    triangles->addTriangle(v1, v3, v4, "Textures/Fault Zone.png");

    //selection->selectVertex(v3);

    /*
    int a = renderManager->addLineVertex(0.0f, 0.0f, 255, 0, 0, 255);
    int b = renderManager->addLineVertex(200.0f, 100.0f, 0, 255, 0, 255);
    int l = renderManager->addLine(a, b);
    renderManager->drawLine(l);

    int tv1 = renderManager->addTriangleVertex(150, 150, 0, 1, 255, 255, 255, 255);
    int tv2 = renderManager->addTriangleVertex(300, 150, 1, 1, 255, 255, 255, 255);
    int tv3 = renderManager->addTriangleVertex(300, 300, 1, 0, 255, 255, 255, 255);
    int t = renderManager->addTriangle(tv1, tv2, tv3, "Textures/Canyon.png");

    renderManager->drawTriangle(t);

    renderManager->removeLine(l);
    renderManager->removeLineVertex(a);
    renderManager->removeLineVertex(b);

    renderManager->removeTriangle(t);
    renderManager->removeTriangleVertex(tv1);
    renderManager->removeTriangleVertex(tv2);
    renderManager->removeTriangleVertex(tv3);
    */
}

void Core::mainLoop() {

    SDL_Event event;
    bool done = false;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (actionHandler != nullptr) {
                if (actionHandler->handleEvent(&event)) {
                    delete actionHandler;
                    actionHandler = nullptr;
                }
            }
            else {
                switch (event.type) {
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            const Uint8* keyState = SDL_GetKeyboardState(NULL);
                            if (keyState[SDL_SCANCODE_LCTRL]) {
                                actionHandler = new TriangleCreationHandler(selection, triangles, &actionManager, renderManager, selectionLayer, screenHeight);
                            }
                        }
                        else if (event.button.button == SDL_BUTTON_RIGHT) {
                            vector<int> newVertices;
                            int v = triangles->getClosestVertex(event.button.x, screenHeight - event.button.y);
                            if (v != -1) {
                                //std::cout<<"v = "<<v<<std::endl;
                                newVertices.push_back(v);
                                SelectVertices* selectVertices;
                                const Uint8* keyState = SDL_GetKeyboardState(NULL);
                                if (keyState[SDL_SCANCODE_LSHIFT])
                                    selectVertices = new SelectVertices(selection, newVertices);
                                else
                                    selectVertices = new SelectVertices(selection, newVertices, true);
                                actionManager.pushAction(selectVertices);
                            }
                        }
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                            case SDLK_a:
                            {
                                if (!selection->empty()) {
                                    vector<int> selectedVertices = selection->getSelectedVertices();
                                    SelectVertices* deselectAll = new SelectVertices(selection, selectedVertices);
                                    actionManager.pushAction(deselectAll);
                                }
                                break;
                            }
                            case SDLK_z:
                            {
                                const Uint8* keyState = SDL_GetKeyboardState(NULL);
                                if (keyState[SDL_SCANCODE_LCTRL]) {
                                    if (keyState[SDL_SCANCODE_LSHIFT])
                                        actionManager.redoAction();
                                    else
                                        actionManager.undoAction();
                                }
                                break;
                            }
                            case SDLK_x:
                            {
                                if (!selection->empty()) {
                                    RemoveSelection* removeSelection = new RemoveSelection(selection, triangles);
                                    actionManager.pushAction(removeSelection);
                                }
                                break;
                            }
                            case SDLK_g:
                            {
                                if (!selection->empty()) {
                                    actionHandler = new MoveHandler(selection, triangles, &actionManager);
                                }
                                break;
                            }
                            case SDLK_s:
                            {
                                vector<int> selectedVertices = selection->getSelectedVertices();
                                if (selectedVertices.size() > 1) {
                                    actionHandler = new ScaleHandler(selection, triangles, &actionManager, screenHeight);
                                }
                                break;
                            }
                            case SDLK_r:
                            {
                                vector<int> selectedVertices = selection->getSelectedVertices();
                                if (selectedVertices.size() > 1) {
                                    actionHandler = new RotationHandler(selection, triangles, &actionManager, screenHeight);
                                }
                                break;
                            }
                            case SDLK_f:
                            {
                                vector<int> selectedVertices = selection->getSelectedVertices();
                                if (selectedVertices.size() == 3) {
                                    vector<int> adjacentTriangles = triangles->getAdjacentTriangles(selectedVertices[0]);
                                    bool noTriangleYet = true;
                                    for (unsigned int i = 0; i < adjacentTriangles.size(); i++) {
                                        if (triangles->triangleContainsVertex(adjacentTriangles[i], selectedVertices[1]) && triangles->triangleContainsVertex(adjacentTriangles[i], selectedVertices[2]))
                                            noTriangleYet = false;
                                    }
                                    if (noTriangleYet) {
                                        FillTriangle* fillTriangle = new FillTriangle(selection, triangles, selectedVertices[0], selectedVertices[1], selectedVertices[2]);
                                        actionManager.pushAction(fillTriangle);
                                    }
                                }
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    case SDL_QUIT:
                        done = true;
                        break;
                    default:
                        break;
                }
            }
        }
        frameRender();
    }

    /*float sum = 0;
    float timeStep = 1.0f/60.0f;
    int stepsTotal;
    int stepsToDo;
    int stepsDone = 0;

    bool particleFollowsMouse = false;

	bool running = true;
	while (running) {
		sf::Time elapsedTime = clock.getElapsedTime();
        clock.restart();
		
        sf::Event event;

		while (app.pollEvent(event)) {

            if (actionHandler != nullptr) {
                if (actionHandler->handleEvent(event)) {
                    delete actionHandler;
                    actionHandler = nullptr;
                }
            }
            else {
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {*/
                    /*selection->clearSelection();
                    int v = triangles->getClosestVertex(event.mouseButton.x, screenHeight - event.mouseButton.y);
                    if (v != -1)
                        selection->addVertex(v);*/

                    /*vector<int> newVertices;
                    int v = triangles->getClosestVertex(event.mouseButton.x, screenHeight - event.mouseButton.y);
                    if(v != -1) {
                        newVertices.push_back(v);
                        SelectVertices* selectVertices;
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            selectVertices = new SelectVertices(selection, newVertices);
                        else
                            selectVertices = new SelectVertices(selection, newVertices, true);
                        actionManager.pushAction(selectVertices);
                    }

                    particleFollowsMouse = true;

                    //std::cout<<v<<std::endl;
                    //std::cout<<triangles->getClosestVertex(event.mouseButton.x, screenHeight - event.mouseButton.y)<<std::endl;
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::A)) {
                    vector<int> selectedVertices = selection->getSelectedVertices();
                    if (!selectedVertices.empty()) {
                        SelectVertices* deselectAll = new SelectVertices(selection, selectedVertices);
                        actionManager.pushAction(deselectAll);
                    }
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::U)) {
                    actionManager.undoAction();
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::O)) {
                    actionManager.redoAction();
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::X)) {
                    vector<int> selectedVertices = selection->getSelectedVertices();
                    if (!selectedVertices.empty()) {
                        RemoveSelection* removeSelection = new RemoveSelection(selection, triangles);
                        actionManager.pushAction(removeSelection);
                    }
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::G)) {
                    vector<int> selectedVertices = selection->getSelectedVertices();
                    if (!selectedVertices.empty()) {
                        MoveSelection* moveSelection = new MoveSelection(selection, triangles);
                        actionHandler = new MoveHandler(selection, triangles, moveSelection, &actionManager, &app);
                    }
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S)) {
                    vector<int> selectedVertices = selection->getSelectedVertices();
                    if (selectedVertices.size() > 1) {
                        ScaleSelection* scaleSelection = new ScaleSelection(selection, triangles);
                        actionHandler = new ScaleHandler(selection, triangles, scaleSelection, &actionManager, &app);
                    }
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)) {
                    vector<int> selectedVertices = selection->getSelectedVertices();
                    if (selectedVertices.size() > 1) {
                        RotateSelection* rotateSelection = new RotateSelection(selection, triangles);
                        actionHandler = new RotationHandler(selection, triangles, rotateSelection, &actionManager, &app);
                    }
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::C)) {
                    CreateTriangle* createTriangle = new CreateTriangle(selection, triangles);
                    actionHandler = new TriangleCreationHandler(selection, selectionLayer, renderManager, createTriangle, &actionManager, &app);
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F)) {
                    vector<int> selectedVertices = selection->getSelectedVertices();
                    if (selectedVertices.size() == 3) {
                        vector<int> adjacentTriangles = triangles->getAdjacentTriangles(selectedVertices[0]);
                        bool noTriangleYet = true;
                        for (unsigned int i = 0; i < adjacentTriangles.size(); i++) {
                            if (triangles->triangleContainsVertex(adjacentTriangles[i], selectedVertices[1]) && triangles->triangleContainsVertex(adjacentTriangles[i], selectedVertices[2]))
                                noTriangleYet = false;
                        }
                        if (noTriangleYet) {
                            FillTriangle* fillTriangle = new FillTriangle(selection, triangles, selectedVertices[0], selectedVertices[1], selectedVertices[2]);
                            actionManager.pushAction(fillTriangle);
                        }
                    }
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P)) {
                    actionHandler = new PaintColorHandler(triangles, &actionManager, &app);
                }
            }
			
			if (event.type == sf::Event::Closed)
				running = false;
			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				running = false;
            else if (event.type == sf::Event::MouseMoved)
                lights[3].setPosition(event.mouseMove.x, screenHeight - event.mouseMove.y);

            //else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                //particleSystem->step();
            //}
        //}

        if (particleFollowsMouse) {
            sf::Vector2i p = sf::Mouse::getPosition();
            particleSystem->setMouseParticle(p.x, screenHeight - p.y);
        }

        sum += elapsedTime.asSeconds();

        while (sum >= 1.0f) {
            stepsDone -= 60;
            sum -= 1.0f;
        }

        stepsTotal = sum/timeStep;
        stepsToDo = stepsTotal - stepsDone;
        stepsDone = stepsTotal;

        for (int i = 0; i < stepsToDo; i++)
            particleSystem->step();
		
		frameRender();
		
		
		app.display();
    }*/
}

void Core::frameRender() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    triangles->draw();
    selection->draw();
    selectionLayer->draw();

    // Swap our back buffer to the front
    SDL_GL_SwapWindow(mainwindow);
}

void Core::close() {
    delete renderManager;
    delete resourceManager;
    delete selection;
    delete triangles;

    // Delete our opengl context, destroy our window, and shutdown SDL
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    /*delete particleSystem;
	deleteFramebuffers();*/
}

}
