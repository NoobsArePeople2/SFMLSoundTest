#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <TGUI/TGUI.hpp>

#include <iostream>
#include <sstream>

#include <vector>
#include <string>

#include "ResourcePath.h"

int main()
{
    unsigned int width = 800;
    unsigned int height = 600;
    sf::RenderWindow win(sf::VideoMode(width, height, 32), "SFML Sound Test");
    win.setFramerateLimit(60);

    tgui::Gui gui(win);

    // Loop values
    float accumulator = 0.0f;
    int ticks = 0;
    sf::Clock clock;
    float updateInterval = 1.0f / 100.0f;
    int deathSpiral = 10;

    // GUI
    sf::Font font = sf::Font();
    int fontSize = 14;
    if (!font.loadFromFile(resourcePath("arial.ttf")))
    {
        printf("Unable to load font!\n");
        return 1;
    }

    gui.setGlobalFont(font);

    int btnWidth = 200;
    int btnHeight = 50;
    std::string guiConf(resourcePath("TGUI/objects/Black.conf"));

    const int chickenId = 1;
    tgui::Button::Ptr chickenBtn(gui);
    chickenBtn->load(guiConf);
    chickenBtn->setSize(btnWidth, btnHeight);
    chickenBtn->setPosition(0, (height - btnHeight) / 2);
    chickenBtn->setText("Play Chicken");
    chickenBtn->bindCallback(tgui::Button::LeftMouseClicked);
    chickenBtn->setCallbackId(chickenId);

    const int sirenId = 2;
    tgui::Button::Ptr sirenBtn(gui);
    sirenBtn->load(guiConf);
    sirenBtn->setSize(btnWidth, btnHeight);
    sirenBtn->setPosition(width * 0.25f, (height - btnHeight) / 2);
    sirenBtn->setText("Play Siren");
    sirenBtn->bindCallback(tgui::Button::LeftMouseClicked);
    sirenBtn->setCallbackId(sirenId);

    const int bouncesId = 3;
    tgui::Button::Ptr bouncesBtn(gui);
    bouncesBtn->load(guiConf);
    bouncesBtn->setSize(btnWidth, btnHeight);
    bouncesBtn->setPosition(width * 0.5f, (height - btnHeight) / 2);
    bouncesBtn->setText("Play Bounces");
    bouncesBtn->bindCallback(tgui::Button::LeftMouseClicked);
    bouncesBtn->setCallbackId(bouncesId);

    const int phoneId = 4;
    tgui::Button::Ptr phoneBtn(gui);
    phoneBtn->load(guiConf);
    phoneBtn->setSize(btnWidth, btnHeight);
    phoneBtn->setPosition(width * 0.75f, (height - btnHeight) / 2);
    phoneBtn->setText("Play Phone");
    phoneBtn->bindCallback(tgui::Button::LeftMouseClicked);
    phoneBtn->setCallbackId(phoneId);

    // Load Sounds
    sf::SoundBuffer chickenBuffer;

    if (!chickenBuffer.loadFromFile(resourcePath("cartoon-chicken.ogg")))
    {
        printf("Unable to load 'cartoon-chicken.ogg\n");
        return 1;
    }

    sf::Sound chickenSound;
    chickenSound.setBuffer(chickenBuffer);

    sf::SoundBuffer sirenBuffer;
    if (!sirenBuffer.loadFromFile(resourcePath("cartoon-siren-whistle.wav")))
    {
        printf("Unable to load 'cartoon-siren-whistle.wav\n");
        return 1;
    }

    sf::Sound sirenSound;
    sirenSound.setBuffer(sirenBuffer);

    sf::SoundBuffer bouncesBuffer;
    if (!bouncesBuffer.loadFromFile(resourcePath("chorused-bounces.wav")))
    {
        printf("Unable to load 'chorused-bounces.wav\n");
        return 1;
    }

    sf::Sound bouncesSound;
    bouncesSound.setBuffer(bouncesBuffer);

    sf::SoundBuffer phoneBuffer;
    if (!phoneBuffer.loadFromFile(resourcePath("phone-voice-cartoon.wav")))
    {
        printf("Unable to load 'phone-voice-cartoon.wav\n");
        return 1;
    }

    sf::Sound phoneSound;
    phoneSound.setBuffer(phoneBuffer);

    while (win.isOpen())
    {
        accumulator += clock.restart().asSeconds();
        while (accumulator >= updateInterval && ticks < deathSpiral)
        {
            accumulator -= updateInterval;
            ++ticks;
            sf::Event event;
            while (win.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    win.close();
                }

                gui.handleEvent(event);
            }

            tgui::Callback callback;
            while (gui.pollCallback(callback))
            {
                switch (callback.id)
                {
                case chickenId:
                    printf("cluck cluck\n");
                    chickenSound.play();
                    break;

                case sirenId:
                    printf("siren\n");
                    sirenSound.play();
                    break;

                case bouncesId:
                    printf("boing boing\n");
                    bouncesSound.play();
                    break;

                case phoneId:
                    printf("ring riiiing\n");
                    phoneSound.play();
                    break;
                }
            }

        }

        // Draw
        win.clear(sf::Color(0, 0, 0));

        gui.draw();

        win.display();
        ticks = 0;
    }

   return 0;
}
