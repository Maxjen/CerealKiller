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

/*Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    char* vsSource = fileTostring(vertexShaderPath);
    char* fsSource = fileTostring(fragmentShaderPath);

    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, (const char **)&vsSource, NULL);
    glCompileShader(vertexShaderId);
    printLog(vertexShaderId);

    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, (const char **)&fsSource, NULL);
    glCompileShader(fragmentShaderId);
    printLog(fragmentShaderId);

    free(vsSource);
    free(fsSource);

    programId = glCreateProgram();
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);
    printLog(programId);
}

Shader::~Shader() {
    GLenum ErrorCheckValue = glGetError();

    glUseProgram(0);

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteProgram(programId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        fprintf(
            stderr,
            "ERROR: Could not destroy the shaders: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        //exit(-1);
    }
}

char* Shader::fileTostring(const char *path) {
    FILE *fd;
    long len, r;
    char *str;

    if (!(fd = fopen(path, "r")))
    {
        fprintf(stderr, "Can't open file '%s' for reading\n", path);
        return NULL;
    }

    fseek(fd, 0, SEEK_END);
    len = ftell(fd);

    printf("File '%s' is %ld long\n", path, len);

    fseek(fd, 0, SEEK_SET);

    if (!(str = (char*)malloc(len * sizeof(char))))
    {
        fprintf(stderr, "Can't malloc space for '%s'\n", path);
        return NULL;
    }

    r = fread(str, sizeof(char), len, fd);

    str[r - 1] = '\0'; // Shader sources have to term with null

    fclose(fd);

    return str;
}

void Shader::printLog(GLuint obj) {
    int infologLength = 0;
    int maxLength;

    if(glIsShader(obj))
        glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
    else
        glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);

    char infoLog[maxLength];

    if (glIsShader(obj))
        glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
    else
        glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);

    if (infologLength > 0)
        printf("%s\n",infoLog);
}*/

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

    // Clear our buffer with a black background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap our back buffer to the front
    SDL_GL_SwapWindow(mainwindow);

    SDL_Delay(2000);

    //actionHandler = nullptr;
	
    //resourceManager = new ResourceManager();
	
	
    /*printf("Initializing glew\n");
	GLenum err = glewInit();
	if(err != GLEW_OK) {
		fprintf(stderr, "INFO: glew couldn't be initialized. Exit\n");
		close();
	}
	if (GLEW_VERSION_2_0)
		fprintf(stderr, "INFO: OpenGL 2.0 supported, proceeding\n");
	else
	{
		fprintf(stderr, "INFO: OpenGL 2.0 not supported. Exit\n");
		close();
    }*/

    /*triangleShader = new Shader("triangle.vert", "triangle.frag");

    pointLineShader = new Shader("pointLine.vert", "pointLine.frag");

    radialBlurShader = new Shader("radialBlur.vert", "radialBlur.frag");

    renderManager = new RenderManager(resourceManager, pointLineShader->getProgramId(), pointLineShader->getProgramId(), triangleShader->getProgramId());

    triangles = new Triangles(renderManager);
    selection = new Selection(renderManager, triangles);
    selectionLayer = new Layer(renderManager);

    particleSystem = new ParticleSystem(renderManager);

    glPointSize(5.0f);*/
	
    /*glShadeModel(GL_SMOOTH);
	glViewport(0, 0, screenWidth, screenHeight);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -128, 128);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Set the color and depth clear values
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	glDepthFunc(GL_LEQUAL);*/
}

void Core::mainLoop() {
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

            /*else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                particleSystem->step();
            }*/
        /*}

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

/*void Core::frameRender() {
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

}*/

/// Print out the information log for a shader object 
/// @arg obj handle for a program object
/*static void printProgramInfoLog(GLuint obj)
{
	GLint infologLength = 0, charsWritten = 0;
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 2) {
		GLchar* infoLog = new GLchar [infologLength];
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cerr << infoLog << std::endl;
		delete infoLog;
	}
}*/

void Core::close() {
    // Delete our opengl context, destroy our window, and shutdown SDL
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    /*glDeleteTextures(1, &lightTex);
	
    delete selection;
    delete triangles;
    delete particleSystem;
    delete renderManager;
    delete resourceManager;

	
	deleteFramebuffers();
	
    delete triangleShader;
    delete pointLineShader;

    delete radialBlurShader;
	*/
}

}
