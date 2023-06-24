#define NOMINMAX
#include <iostream>
#include <thread>
#include <fstream>
#include <stdlib.h>
#include "unit.h"
#include "MapRoomsGen.h"
using namespace sf;

		int Map[SizeMapConst][SizeMapConst];
		double GrassMap[SizeMapConst][SizeMapConst];
		int FoodCurent = 0;
		Units R(10, 15, 1, 1, 1, 1);
		bool IsItStart = false;

	thread t4([&]() {
			int buttonPosx = 0, buttonPosy = 0;

			double TpsTimer = 0, t1 = 0, t2 = 0;
			int tps = 0, IterCounter = 0;
			int i = 0, j = 0;

			bool DrawScreen = true, MouseButtonPressd = false, ButtonBul[9], FieldBool[8], FieldWrite[8];
			for (i = 0; i < 8; i++)FieldWrite[i] = false;
			double tViev = 0;
			int SizeWindX = 630, SizeWindY = 440;

			RenderWindow window(VideoMode(SizeWindX, SizeWindY), "Start");

			string s;
			Font font;
			font.loadFromFile("fonts/timesnewromanpsmt.ttf");
			Text text("", font, 20);
			text.setStyle(sf::Text::Bold);
			String playerInput;
			String PlayerInput[8];
			Text playerText("", font, 20);
			playerText.setStyle(sf::Text::Bold);

			Sprite ButtonSprite[2];
			Image ButtonImage;
			Texture ButtonTexture;
			RectangleShape tana(Vector2f(180, 30));
			{
				ButtonImage.loadFromFile("images/button1.png");
				ButtonTexture.loadFromImage(ButtonImage);
				ButtonSprite[0].setTexture(ButtonTexture);
				ButtonSprite[0].setTextureRect(IntRect(0, 0, 32, 32));
				ButtonSprite[1].setTexture(ButtonTexture);
				ButtonSprite[1].setTextureRect(IntRect(32, 0, 32, 32));

			}


			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == sf::Event::TextEntered)
					{
						if ((event.text.unicode > 47 && event.text.unicode < 58) || event.text.unicode == 46 || event.text.unicode == 45)
						{
							//playerInput += event.text.unicode;
							for (i = 0; i < 8; i++) {
								if (FieldWrite[i]) {
									if (event.text.unicode == 45) {
										if (PlayerInput[i] == "") {
											PlayerInput[i] += event.text.unicode;
										}
									}
									else {
										PlayerInput[i] += event.text.unicode;
									}
								}
							}
							playerText.setString(playerInput);
						}
					}
				}
				window.clear();

				IterCounter++;
				t1 = clock();

				tViev += ((double)t1 / CLOCKS_PER_SEC - (double)t2 / CLOCKS_PER_SEC);
				if (tViev > 0.01) {
					tViev = 0;
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						IsItStart = true;
						window.close();
						return 0;
					}
					if (Keyboard::isKeyPressed(Keyboard::Delete)) {
						for (i = 0; i < 8; i++) {
							PlayerInput[i] = "";
						}
						playerInput = "";
					}
				}
				if ((Mouse::isButtonPressed(Mouse::Left)) && MouseButtonPressd) {
					MouseButtonPressd = false;
					if (ButtonBul[0]) {
						s = PlayerInput[0];
						MapSeed = atof(s.c_str());
						playerInput = "";
						PlayerInput[0] = "";
					}
					else
						if (ButtonBul[1]) {
							s = PlayerInput[1];
							startUnits = atof(s.c_str());
							playerInput = "";
							PlayerInput[1] = "";
						}
						else
							if (ButtonBul[2]) {
								s = PlayerInput[2];
								StartUnitStats[0] = atof(s.c_str());
								playerInput = "";
								PlayerInput[2] = "";
							}
							else
								if (ButtonBul[3]) {
									s = PlayerInput[3];
									StartUnitStats[1] = atof(s.c_str());
									playerInput = "";
									PlayerInput[3] = "";
								}
								else
									if (ButtonBul[4]) {
										s = PlayerInput[4];
										StartUnitStats[2] = atof(s.c_str());
										playerInput = "";
										PlayerInput[4] = "";
									}
									else
										if (ButtonBul[5]) {
											s = PlayerInput[5];
											StartUnitStats[3] = atof(s.c_str());
											playerInput = "";
											PlayerInput[5] = "";
										}
										else
											if (ButtonBul[6]) {
												s = PlayerInput[6];
												StartUnitStats[4] = atof(s.c_str());
												playerInput = "";
												PlayerInput[6] = "";
											}
											else
												if (ButtonBul[7]) {
													s = PlayerInput[7];
													StartUnitStats[5] = atof(s.c_str());
													playerInput = "";
													PlayerInput[7] = "";
												}
												else
													if (ButtonBul[8]) {
														cout << "Start!\n";
														IsItStart = true;
														window.close();
													}
							else
								if (FieldBool[0]) {
									for (i = 0; i < 8; i++) {
										FieldWrite[i] = false;
									}
									FieldWrite[0] = true;
								}
								else
									if (FieldBool[1]) {
										for (i = 0; i < 8; i++) {
											FieldWrite[i] = false;
										}
										FieldWrite[1] = true;
									}
									else
										if (FieldBool[2]) {
											for (i = 0; i < 8; i++) {
												FieldWrite[i] = false;
											}
											FieldWrite[2] = true;
										}
										else
											if (FieldBool[3]) {
												for (i = 0; i < 8; i++) {
													FieldWrite[i] = false;
												}
												FieldWrite[3] = true;
											}
											else
												if (FieldBool[4]) {
													for (i = 0; i < 8; i++) {
														FieldWrite[i] = false;
													}
													FieldWrite[4] = true;
												}
												else
													if (FieldBool[5]) {
														for (i = 0; i < 8; i++) {
															FieldWrite[i] = false;
														}
														FieldWrite[5] = true;
													}
													else
														if (FieldBool[6]) {
															for (i = 0; i < 8; i++) {
																FieldWrite[i] = false;
															}
															FieldWrite[6] = true;
														}
														else
															if (FieldBool[7]) {
																for (i = 0; i < 8; i++) {
																	FieldWrite[i] = false;
																}
																FieldWrite[7] = true;
															}
				}
				if (!(Mouse::isButtonPressed(Mouse::Left))) {
					MouseButtonPressd = true;
				}




				TpsTimer += ((double)t1 / CLOCKS_PER_SEC - (double)t2 / CLOCKS_PER_SEC);

				t2 = t1;
				if (TpsTimer > 1) {
					TpsTimer = 0;
					//cout << "fps: " << IterCounter << endl;
					tps = IterCounter;
					IterCounter = 0;
				}

				{
					buttonPosx = 220;
					buttonPosy = 40;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[0] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[0] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx -20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[0] = true;
					}
					else {
						FieldBool[0] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[0]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Map Seed: " + to_string(MapSeed));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 220;
					buttonPosy = 110;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[1] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[1] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx - 20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[1] = true;
					}
					else {
						FieldBool[1] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[1]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Start Units: " + to_string(startUnits));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 220 + 350;
					buttonPosy = 40;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[2] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[2] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx - 20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[2] = true;
					}
					else {
						FieldBool[2] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[2]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Start units vision: " + to_string(StartUnitStats[0]));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 220 + 350;
					buttonPosy = 110;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[3] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[3] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx - 20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[3] = true;
					}
					else {
						FieldBool[3] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[3]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Start units flair: " + to_string(StartUnitStats[1]));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 220 + 350;
					buttonPosy = 180;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[4] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[4] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx - 20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[4] = true;
					}
					else {
						FieldBool[4] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[4]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Start units size: " + to_string(StartUnitStats[2]));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 220 + 350;
					buttonPosy = 250;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[5] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[5] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx - 20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[5] = true;
					}
					else {
						FieldBool[5] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[5]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Start units metabolism: " + to_string(StartUnitStats[3]));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 220 + 350;
					buttonPosy = 320;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[6] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[6] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx - 20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[6] = true;
					}
					else {
						FieldBool[6] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[6]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Start units speed: " + to_string(StartUnitStats[4]));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 220 + 350;
					buttonPosy = 390;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[7] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[7] = false;
						window.draw(ButtonSprite[1]);
					}
					if (Mouse::getPosition(window).x >= buttonPosx - 200 && Mouse::getPosition(window).x <= buttonPosx - 20 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
						FieldBool[7] = true;
					}
					else {
						FieldBool[7] = false;
					}
					tana.setPosition(buttonPosx - 200, buttonPosy + 1);
					window.draw(tana);
					playerText.setFillColor(Color::Black);
					playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
					playerText.setString(PlayerInput[7]);
					window.draw(playerText);

					text.setFillColor(Color::White);
					text.setString("Start units temperature: " + to_string(StartUnitStats[5]));
					text.setPosition(buttonPosx - 200, buttonPosy - 30);
					window.draw(text);
				}
				{
					buttonPosx = 90;
					buttonPosy = 390;
					if (Mouse::getPosition(window).x >= buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 32 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
						ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
						ButtonBul[8] = true;
						window.draw(ButtonSprite[0]);
					}
					else {
						ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
						ButtonBul[8] = false;
						window.draw(ButtonSprite[1]);
					}

					text.setFillColor(Color::White);
					text.setString("Start: ");
					text.setPosition(buttonPosx - 60, buttonPosy);
					window.draw(text);
				}

				window.display();
			}
			});

	thread t3([&]() {
		while (!IsItStart) { cout << ""; }

		FILE* pipe = _popen("gnuplot -p", "w");

		int i, DrawGra=0, PrevDrawGra,NextDrawGra;
		double tViev = 0, tRedr=2.5, t1 = 0, t2 = 0;
		bool ChGraph[2], MouseButtonPressd = false, FirstTimer = true;
		RenderWindow window(VideoMode(700, 520), "Graphs");

		string s[8];
		Font font;
		font.loadFromFile("fonts/timesnewromanpsmt.ttf");
		Text text("", font, 20);
		text.setStyle(sf::Text::Bold);

		Image ArrowDownImage;
		Sprite ArrowDownSprite;
		Texture ArrowDownTexture;
		Image Graphs[8];
		Texture GraphsTexture[8];
		Sprite GraphsSprite[8];
		{
			ArrowDownImage.loadFromFile("images/arrowdown.png");
			ArrowDownTexture.loadFromImage(ArrowDownImage);
			ArrowDownSprite.setTexture(ArrowDownTexture);
			ArrowDownSprite.setTextureRect(IntRect(0, 0, 23, 13));

			s[0] = "Vision";
			s[1] = "Flair";
			s[2] = "Size";
			s[3] = "Metabolism";
			s[4] = "Speed";
			s[5] = "Temperature";
			s[6] = "Units";
			s[7] = "Food";
			Graphs[0].loadFromFile("images/Graph/Vision.png");
			Graphs[1].loadFromFile("images/Graph/Flair.png");
			Graphs[2].loadFromFile("images/Graph/Size.png");
			Graphs[3].loadFromFile("images/Graph/Metabolism.png");
			Graphs[4].loadFromFile("images/Graph/Speed.png");
			Graphs[5].loadFromFile("images/Graph/Temperature.png");
			Graphs[6].loadFromFile("images/Graph/UnitsPerTime.png");
			Graphs[7].loadFromFile("images/Graph/FoodPerTime.png");
			for (i = 0; i < 8; i++) {
				GraphsTexture[i].loadFromImage(Graphs[i]);
				GraphsSprite[i].setTexture(GraphsTexture[i]);
				GraphsSprite[i].setTextureRect(IntRect(0, 0, 640, 480));
				GraphsSprite[i].setScale(1, 1);
				GraphsSprite[i].setPosition(0, 40);
			}
		}



		t2 = clock();
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			t1 = clock();
			tViev += ((double)t1 / CLOCKS_PER_SEC - (double)t2 / CLOCKS_PER_SEC);
			tRedr += ((double)t1 / CLOCKS_PER_SEC - (double)t2 / CLOCKS_PER_SEC);
			if (FirstTimer) { FirstTimer = false; tRedr += 2.5; }
			if (tViev > 0.01) {
				tViev = 0;
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					return 0;
				}
			}
			if (tRedr >= 5) {
				{
					Graphs[0].loadFromFile("images/Graph/Vision.png");
					Graphs[1].loadFromFile("images/Graph/Flair.png");
					Graphs[2].loadFromFile("images/Graph/Size.png");
					Graphs[3].loadFromFile("images/Graph/Metabolism.png");
					Graphs[4].loadFromFile("images/Graph/Speed.png");
					Graphs[5].loadFromFile("images/Graph/Temperature.png");
					Graphs[6].loadFromFile("images/Graph/UnitsPerTime.png");
					Graphs[7].loadFromFile("images/Graph/FoodPerTime.png");
					for (i = 0; i < 8; i++) {
						GraphsTexture[i].loadFromImage(Graphs[i]);
						GraphsSprite[i].setTexture(GraphsTexture[i]);
						GraphsSprite[i].setTextureRect(IntRect(0, 0, 640, 480));
						GraphsSprite[i].setScale(1, 1);
						GraphsSprite[i].setPosition(0, 40);
					}
					
				}

				pipe = _popen("gnuplot -p", "w");
				fprintf(pipe, "\nset term pngcairo\n");
				fprintf(pipe, "\nset xlabel \"Generation\"\n");
				fprintf(pipe, "\nset output \"images/Graph/Flair.png\"\n");
				fprintf(pipe, "\nset ylabel \"Flair\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataF.txt' w l notitle\n");
				fflush(pipe);
				fprintf(pipe, "\nset output \"images/Graph/Vision.png\"\n");
				fprintf(pipe, "\nset ylabel \"Vision\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataV.txt' w l notitle\n");
				fflush(pipe);
				fprintf(pipe, "\nset output \"images/Graph/Metabolism.png\"\n");
				fprintf(pipe, "\nset ylabel \"Metabolism\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataM.txt' w l notitle\n");
				fflush(pipe);
				fprintf(pipe, "\nset output \"images/Graph/Speed.png\"\n");
				fprintf(pipe, "\nset ylabel \"Speed\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataS.txt' w l notitle\n");
				fflush(pipe);
				fprintf(pipe, "\nset output \"images/Graph/Temperature.png\"\n");
				fprintf(pipe, "\nset ylabel \"Temperature\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataT.txt' w l notitle\n");
				fflush(pipe);
				fprintf(pipe, "\nset output \"images/Graph/Size.png\"\n");
				fprintf(pipe, "\nset ylabel \"Size\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataSi.txt' w l notitle\n");
				fflush(pipe);
				fprintf(pipe, "\nset xlabel \"Time\"\n");
				fprintf(pipe, "\nset output \"images/Graph/UnitsPerTime.png\"\n");
				fprintf(pipe, "\nset ylabel \"Units\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataUpt.txt' w l notitle\n");
				fflush(pipe);
				fprintf(pipe, "\nset output \"images/Graph/FoodPerTime.png\"\n");
				fprintf(pipe, "\nset ylabel \"Food\"\n");
				fprintf(pipe, "\nplot 'images/Graph/dataFpt.txt' w l notitle\n");
				fflush(pipe);
				_pclose(pipe);
				tRedr -= 5;
			}
			

			if (Mouse::getPosition(window).x >= 660 && Mouse::getPosition(window).x <= 683 && Mouse::getPosition(window).y >= 120 && Mouse::getPosition(window).y <= 133) {
				ChGraph[0] = true;
			}
			else {
				ChGraph[0] = false;
			}
			if (Mouse::getPosition(window).x >= 660 && Mouse::getPosition(window).x <= 683 && Mouse::getPosition(window).y >= 67 && Mouse::getPosition(window).y <= 80) {
				ChGraph[1] = true;
			}
			else {
				ChGraph[1] = false;
			}
			if ((Mouse::isButtonPressed(Mouse::Left)) && MouseButtonPressd) {
				MouseButtonPressd = false;
				if (ChGraph[0]) {
					if (DrawGra == 0) {
						DrawGra = 7;
					}
					else {
						DrawGra--;
					}
				}
				if (ChGraph[1]) {
					if (DrawGra == 7) {
						DrawGra = 0;
					}
					else {
						DrawGra++;
					}
				}
			}
			if (!(Mouse::isButtonPressed(Mouse::Left))) {
				MouseButtonPressd = true;
			}


			ArrowDownSprite.setScale(1, 1);
			ArrowDownSprite.setPosition(660, 120);
			window.draw(ArrowDownSprite);
			ArrowDownSprite.setScale(1, -1);
			ArrowDownSprite.setPosition(660, 80);
			window.draw(ArrowDownSprite);

			if (DrawGra == 0) PrevDrawGra = 7; else PrevDrawGra = DrawGra - 1;
			if (DrawGra == 7) NextDrawGra = 0; else NextDrawGra = DrawGra + 1;


			window.draw(GraphsSprite[DrawGra]);

			text.setString(s[PrevDrawGra]);
			text.setPosition(0, 0);
			window.draw(text);

			text.setFillColor(Color::White);
			text.setString(s[DrawGra]);
			text.setPosition(200, 0);
			window.draw(text);

			text.setFillColor(Color(127, 127, 127));
			text.setString(s[NextDrawGra]);
			text.setPosition(400, 0);
			window.draw(text);

			t2 = t1;
			window.display();
		}

		return 0;

	});

	thread t2([&]() {
		while (!IsItStart) { cout << ""; }
		FILE* output;
		FILE* gp;
		ofstream fout;

		MYSQL* conn;
		MYSQL_RES* res;
		MYSQL_ROW row;
		MYSQL_FIELD* fie;
		string str;
		const char* cstr;

		conn = mysql_init(NULL);
		if (conn == NULL)
		{
			fprintf(stderr, "Error: can't create MySQL-descriptor\n");
		}
		if (!mysql_real_connect(conn, "localhost", "root", "root", "GenCon", NULL, NULL, 0))
		{
			fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
		}
		else
		{
			fprintf(stdout, "Success!\n");
		}

		mysql_set_character_set(conn, "cp1251");

		list<double> Gr;
		list<double>::iterator Grit;
		double vr = 0, vr2 = 0;
		int TierCoun = 1;
		int Counter = 0;
		double Tc1 = 0, Tc2 = 0, Timer1 = 0, Timer2 = 0, Timer3 = 0;
		int i=0, j=0,k;
		MapSeed = MapGen(Map);
		str = string("INSERT INTO `Map` VALUE (") + to_string(MapSeed) + string(",") + to_string(SizeMap) + string(")");
		cstr = str.c_str();
		mysql_query(conn, cstr);
		//cout << str << endl;
		int TimeCounter = 0;
		{
			fout.open("images/Graph/dataUpt.txt");
			fout << TimeCounter << " " << startUnits << "\n";
			fout.close();
		}
		{
			fout.open("images/Graph/dataFpt.txt");
			fout << TimeCounter << " " << 0 << "\n";
			fout.close();
		}
		double r;
		for (i = 0; i < SizeMapConst; i++) {
			for (j = 0; j < SizeMapConst; j++) {
				ItemMap[i][j] = Map[i][j];
				FoodMap[i][j] = 0;
				if (Map[i][j] == 0) {
					GrassMap[i][j] = (double)(rand()) / RAND_MAX;
				}
				else {
					GrassMap[i][j] = -1;
				}
			}
		}
		//PrintMapASCII(GrassMap);



		list<Units> UnitsList;

		i = 0;
		while (i < startUnits) {
			int p = rand() % SizeMapConst;
			int q = rand() % SizeMapConst;
			if (ItemMap[p][q] == 0) {
				R.SetStats(1, StartUnitStats[0], StartUnitStats[1], StartUnitStats[2], StartUnitStats[3], StartUnitStats[4], StartUnitStats[5], p, q);
				str = R.GetSQL();
				cstr = str.c_str();
				mysql_query(conn, cstr);
				//cout << str << endl;
				UnitsList.push_back(R);
				i++;
				UnitNum++;
			}
		}




		list<Units>::iterator UnitsListIter = UnitsList.begin();

		list<Food> Oran;
		Food Oran1(1, 10, 0, 0);
		Oran.push_back(Oran1);
		list<Food>::iterator OranIter = Oran.begin();


		R.ReMap();
		R.FindFoodFlair();
		double TemDiff;
		//R.FindFoodVision();
		//R.PrintWayMapWay();
		Tc2 = clock();
		while (true) {
			Tc1 = clock();
			Timer1 += ((double)Tc1 / CLOCKS_PER_SEC - (double)Tc2 / CLOCKS_PER_SEC);
			Timer2 += ((double)Tc1 / CLOCKS_PER_SEC - (double)Tc2 / CLOCKS_PER_SEC);
			Timer3 += ((double)Tc1 / CLOCKS_PER_SEC - (double)Tc2 / CLOCKS_PER_SEC);
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				mysql_close(conn);
				return 0;
			}
			for (i = 0; i < SizeMapConst; i++) {
				for (j = 0; j < SizeMapConst; j++) {
					if (GrassMap[i][j]>1 && FoodMap[i][j] == 0 && ItemMap[i][j]==0) {
						//cout << i << " " << j << endl;
						Oran1 = Food(3, 10, i, j);
						Oran.push_back(Oran1);
						FoodCurent++;
						GrassMap[i][j] -= 1;
						ItemMap[i][j] = 3;
						FoodMap[i][j] = Oran1.GetType();
					}
				}
			}
			/*if (FoodCurent < FoodNum) {
				int p = rand() % SizeMapConst;
				int q = rand() % SizeMapConst;
				if (ItemMap[p][q] == 0) {
					Oran1 = Food(1, 10, p, q);
					Oran.push_back(Oran1);
					FoodCurent++;
					ItemMap[p][q] = 3;
					FoodMap[p][q] = Oran1.GetType();
				}
			}*/
			if (Timer2 > 0.1 / (double)GameSpeed) {
				for (UnitsListIter = UnitsList.begin(); UnitsListIter != UnitsList.end(); UnitsListIter++) {
					TemDiff = 0.01 * pow(fabs(TemperatuteM + 5.0 - (*UnitsListIter).GetTemperature()), 2) + 1;

					(*UnitsListIter).ChangeStamin((double)(*UnitsListIter).GetMetabolism() * (double)(*UnitsListIter).GetSpeed()/10);
					if ((*UnitsListIter).GetStamin() >= 100) {
						(*UnitsListIter).FindFoodFlair();
						(*UnitsListIter).StepToGoal();
						(*UnitsListIter).ChangeStamin(-100);
					}
					(*UnitsListIter).OnFood(Oran, FoodCurent);
					//cout << (*UnitsListIter).GetHungerPoints() << " / " << (*UnitsListIter).GetMaxHungerPoints() << " | " << (*UnitsListIter).GetStamin() << endl;

				}
				Timer2 = 0;
			}

			if (Timer1 > 1/(double)GameSpeed) {

				for (UnitsListIter = UnitsList.begin(); UnitsListIter != UnitsList.end(); UnitsListIter++) {
					TemDiff = 0.01 * pow(fabs(TemperatuteM + 5.0 - (*UnitsListIter).GetTemperature()),2) + 1;

					(*UnitsListIter).ChangeHungerPoints(-0.05 * (double)(*UnitsListIter).GetMetabolism() * TemDiff);
					(*UnitsListIter).ChangeAge(1);
				}
				FoodChek(UnitsList,R, conn);

				for (i = 0; i < SizeMapConst; i++) {
					for (j = 0; j < SizeMapConst; j++) {
						if (GrassMap[i][j] != -1)
							GrassMap[i][j] += 0.01 * soil;
					}
				}
				Timer1 = 0;
			}
		
			if (Timer3 > 5) {
				TimeCounter += 5;
				{
					str = string("SELECT `Tier`,`Vision` FROM `Units` WHERE `Map_seed` = ") + to_string(MapSeed) + string(" ORDER BY `Tier`");
					//cout << str << endl;
					cstr = str.c_str();
					mysql_query(conn, cstr);
					TierCoun = 1; Counter = 0;
					Gr.clear();
					i = 0;
					Gr.push_back(i);
					if (res = mysql_store_result(conn)) {
						Grit = Gr.begin();
						while (row = mysql_fetch_row(res)) {
							vr = strtod(row[0], NULL);
							if (vr == TierCoun) {
								vr2 = strtod(row[1], NULL);
								(*Grit) += vr2;
								Counter++;
							}
							else {
								vr2 = strtod(row[1], NULL);
								//cout << (*Grit) << " " << Counter << endl;
								(*Grit) /= Counter;
								Counter = 1;
								TierCoun++;
								Gr.push_back(vr2);
								Grit++;
							}
						}
					}
					else fprintf(stderr, "%s\n", mysql_error(conn));
					TierCoun = 1;
					(*Grit) /= Counter;
					fout.open("images/Graph/dataV.txt");
					for (Grit = Gr.begin(); Grit != Gr.end(); Grit++) {
						fout << TierCoun << " " << (*Grit) << "\n";
						TierCoun++;
					}
					fout.close();
				}
				{
					str = string("SELECT `Tier`,`Flair` FROM `Units` WHERE `Map_seed` = ") + to_string(MapSeed) + string(" ORDER BY `Tier`");
					//cout << str << endl;
					cstr = str.c_str();
					mysql_query(conn, cstr);
					TierCoun = 1; Counter = 0;
					Gr.clear();
					i = 0;
					Gr.push_back(i);
					if (res = mysql_store_result(conn)) {
						Grit = Gr.begin();
						while (row = mysql_fetch_row(res)) {
							vr = strtod(row[0], NULL);
							if (vr == TierCoun) {
								vr2 = strtod(row[1], NULL);
								(*Grit) += vr2;
								Counter++;
							}
							else {
								vr2 = strtod(row[1], NULL);
								//cout << (*Grit) << " " << Counter << endl;
								(*Grit) /= Counter;
								Counter = 1;
								TierCoun++;
								Gr.push_back(vr2);
								Grit++;
							}
						}
					}
					else fprintf(stderr, "%s\n", mysql_error(conn));
					TierCoun = 1;
					(*Grit) /= Counter;
					fout.open("images/Graph/dataF.txt");
					for (Grit = Gr.begin(); Grit != Gr.end(); Grit++) {
						fout << TierCoun << " " << (*Grit) << "\n";
						TierCoun++;
					}
					fout.close();
				}
				{
					str = string("SELECT `Tier`,`Metabolism` FROM `Units` WHERE `Map_seed` = ") + to_string(MapSeed) + string(" ORDER BY `Tier`");
					//cout << str << endl;
					cstr = str.c_str();
					mysql_query(conn, cstr);
					TierCoun = 1; Counter = 0;
					Gr.clear();
					i = 0;
					Gr.push_back(i);
					if (res = mysql_store_result(conn)) {
						Grit = Gr.begin();
						while (row = mysql_fetch_row(res)) {
							vr = strtod(row[0], NULL);
							if (vr == TierCoun) {
								vr2 = strtod(row[1], NULL);
								(*Grit) += vr2;
								Counter++;
							}
							else {
								vr2 = strtod(row[1], NULL);
								//cout << (*Grit) << " " << Counter << endl;
								(*Grit) /= Counter;
								Counter = 1;
								TierCoun++;
								Gr.push_back(vr2);
								Grit++;
							}
						}
					}
					else fprintf(stderr, "%s\n", mysql_error(conn));
					TierCoun = 1;
					(*Grit) /= Counter;
					fout.open("images/Graph/dataM.txt");
					for (Grit = Gr.begin(); Grit != Gr.end(); Grit++) {
						fout << TierCoun << " " << (*Grit) << "\n";
						TierCoun++;
					}
					fout.close();
				}
				{
					str = string("SELECT `Tier`,`Speed` FROM `Units` WHERE `Map_seed` = ") + to_string(MapSeed) + string(" ORDER BY `Tier`");
					//cout << str << endl;
					cstr = str.c_str();
					mysql_query(conn, cstr);
					TierCoun = 1; Counter = 0;
					Gr.clear();
					i = 0;
					Gr.push_back(i);
					if (res = mysql_store_result(conn)) {
						Grit = Gr.begin();
						while (row = mysql_fetch_row(res)) {
							vr = strtod(row[0], NULL);
							if (vr == TierCoun) {
								vr2 = strtod(row[1], NULL);
								(*Grit) += vr2;
								Counter++;
							}
							else {
								vr2 = strtod(row[1], NULL);
								//cout << (*Grit) << " " << Counter << endl;
								(*Grit) /= Counter;
								Counter = 1;
								TierCoun++;
								Gr.push_back(vr2);
								Grit++;
							}
						}
					}
					else fprintf(stderr, "%s\n", mysql_error(conn));
					TierCoun = 1;
					(*Grit) /= Counter;
					fout.open("images/Graph/dataS.txt");
					for (Grit = Gr.begin(); Grit != Gr.end(); Grit++) {
						fout << TierCoun << " " << (*Grit) << "\n";
						TierCoun++;
					}
					fout.close();
				}
				{
					str = string("SELECT `Tier`,`Temperature` FROM `Units` WHERE `Map_seed` = ") + to_string(MapSeed) + string(" ORDER BY `Tier`");
					//cout << str << endl;
					cstr = str.c_str();
					mysql_query(conn, cstr);
					TierCoun = 1; Counter = 0;
					Gr.clear();
					i = 0;
					Gr.push_back(i);
					if (res = mysql_store_result(conn)) {
						Grit = Gr.begin();
						while (row = mysql_fetch_row(res)) {
							vr = strtod(row[0], NULL);
							if (vr == TierCoun) {
								vr2 = strtod(row[1], NULL);
								(*Grit) += vr2;
								Counter++;
							}
							else {
								vr2 = strtod(row[1], NULL);
								//cout << (*Grit) << " " << Counter << endl;
								(*Grit) /= Counter;
								Counter = 1;
								TierCoun++;
								Gr.push_back(vr2);
								Grit++;
							}
						}
					}
					else fprintf(stderr, "%s\n", mysql_error(conn));
					TierCoun = 1;
					(*Grit) /= Counter;
					fout.open("images/Graph/dataT.txt");
					for (Grit = Gr.begin(); Grit != Gr.end(); Grit++) {
						fout << TierCoun << " " << (*Grit) << "\n";
						TierCoun++;
					}
					fout.close();
				}
				{
					str = string("SELECT `Tier`,`Size` FROM `Units` WHERE `Map_seed` = ") + to_string(MapSeed) + string(" ORDER BY `Tier`");
					//cout << str << endl;
					cstr = str.c_str();
					mysql_query(conn, cstr);
					TierCoun = 1; Counter = 0;
					Gr.clear();
					i = 0;
					Gr.push_back(i);
					if (res = mysql_store_result(conn)) {
						Grit = Gr.begin();
						while (row = mysql_fetch_row(res)) {
							vr = strtod(row[0], NULL);
							if (vr == TierCoun) {
								vr2 = strtod(row[1], NULL);
								(*Grit) += vr2;
								Counter++;
							}
							else {
								vr2 = strtod(row[1], NULL);
								//cout << (*Grit) << " " << Counter << endl;
								(*Grit) /= Counter;
								Counter = 1;
								TierCoun++;
								Gr.push_back(vr2);
								Grit++;
							}
						}
					}
					else fprintf(stderr, "%s\n", mysql_error(conn));
					TierCoun = 1;
					(*Grit) /= Counter;
					fout.open("images/Graph/dataSi.txt");
					for (Grit = Gr.begin(); Grit != Gr.end(); Grit++) {
						fout << TierCoun << " " << (*Grit) << "\n";
						TierCoun++;
					}
					fout.close();
				}
				{
					fout.open("images/Graph/dataUpt.txt", ios::app);
					fout << TimeCounter << " " << UnitNum << "\n";
					fout.close();
				}
				{
					fout.open("images/Graph/dataFpt.txt", ios::app);
					fout << TimeCounter << " " << FoodCurent << "\n";
					fout.close();
				}

				Timer3 -= 5;
			}








			Tc2 = Tc1;
		}
	});

	thread t1([&]() {
		while (!IsItStart) { cout << ""; }
		int buttonPosx = 0, buttonPosy = 0, butoniter=0;

		double TpsTimer = 0, t1 = 0, t2 = 0;
		int tps=0, IterCounter=0;
		int i = 0, j = 0;

		bool DrawScreen = true, MouseButtonPressd = false, ButtonBul[3], FieldBool[3], FieldWrite[3];
		for (i = 0; i < 3; i++)FieldWrite[i] = false;
		double ViewCentX = 500, ViewCentY = 500, ViewZoom = 1, tViev = 0;
		int SizeWindX = 1000, SizeWindY = 1000;

		RenderWindow window(VideoMode(SizeWindX + 300, SizeWindY), "Gen");
		View view(FloatRect(ViewCentX, ViewCentY, 1000, 1000));
		view.setCenter(ViewCentX, ViewCentY);
		view.setViewport(sf::FloatRect(0.f, 0.f, 0.76f, 1.f));
		View MenuView(FloatRect(ViewCentX, ViewCentY, 300, 1000));
		MenuView.setCenter(ViewCentX, ViewCentY);
		MenuView.setViewport(sf::FloatRect(0.76f, 0.f, 0.24f, 1.f));

		string s;
		Font font;
		font.loadFromFile("fonts/timesnewromanpsmt.ttf");
		Text text("", font, 20);
		text.setStyle(sf::Text::Bold);
		String playerInput;
		String PlayerInput[3];
		Text playerText("", font, 20);
		playerText.setStyle(sf::Text::Bold);

		Sprite WallSprite, FloorSprite, FoodSprite1, UnitSprite1, UnitSprite2, FoodSprite2, FoodSprite3, ButtonSprite[2];
		Image heroimage, ButtonImage;
		Texture herotexture, ButtonTexture;
		RectangleShape tana(Vector2f(180, 30));
		RectangleShape BorderW(Vector2f(5, 1000));
		BorderW.setFillColor(Color(100,100,100));
		BorderW.setPosition(350, 0);
		RectangleShape BorderH(Vector2f(300, 5));
		BorderH.setFillColor(Color(100, 100, 100));
		{
			ButtonImage.loadFromFile("images/button1.png");
			ButtonTexture.loadFromImage(ButtonImage);
			ButtonSprite[0].setTexture(ButtonTexture);
			ButtonSprite[0].setTextureRect(IntRect(0,0,32,32));
			ButtonSprite[1].setTexture(ButtonTexture);
			ButtonSprite[1].setTextureRect(IntRect(32, 0, 32, 32));

			heroimage.loadFromFile("images/T3.png");
			herotexture.loadFromImage(heroimage);


			FloorSprite.setTexture(herotexture);
			FloorSprite.setTextureRect(IntRect(0, 0, 32, 32));
			FloorSprite.setPosition(0, 0);

			WallSprite.setTexture(herotexture);
			WallSprite.setTextureRect(IntRect(32, 0, 32, 32));
			WallSprite.setPosition(0, 0);

			FoodSprite1.setTexture(herotexture);
			FoodSprite1.setTextureRect(IntRect(64, 0, 32, 32));
			FoodSprite1.setPosition(0, 0);

			UnitSprite1.setTexture(herotexture);
			UnitSprite1.setTextureRect(IntRect(96, 0, 32, 32));
			UnitSprite1.setPosition(0, 0);

			UnitSprite2.setTexture(herotexture);
			UnitSprite2.setTextureRect(IntRect(128, 0, 32, 32));
			UnitSprite2.setPosition(0, 0);

			FoodSprite2.setTexture(herotexture);
			FoodSprite2.setTextureRect(IntRect(160, 0, 32, 32));
			FoodSprite2.setPosition(0, 0);

			FoodSprite3.setTexture(herotexture);
			FoodSprite3.setTextureRect(IntRect(192, 0, 32, 32));
			FoodSprite3.setPosition(0, 0);
		}


		t2 = clock();
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.type == sf::Event::TextEntered)
				{
					if ((event.text.unicode > 47 && event.text.unicode < 58) || event.text.unicode == 46 || event.text.unicode == 45)
					{
						//playerInput += event.text.unicode;
						for (i = 0; i < 3; i++) {
							if (FieldWrite[i]) {
								if (event.text.unicode == 45) {
									if (PlayerInput[i] == "") {
										PlayerInput[i] += event.text.unicode;
									}
								}
								else {
									PlayerInput[i] += event.text.unicode;
								}
							}
						}
						playerText.setString(playerInput);
					}
				}
			}
			window.setView(view);
			window.clear();
			IterCounter++;
			t1 = clock();

			tViev += ((double)t1 / CLOCKS_PER_SEC - (double)t2 / CLOCKS_PER_SEC);
			if (tViev > 0.01) {
				tViev = 0;/*
				if (Keyboard::isKeyPressed(Keyboard::V)) {
					if (DrawScreen == true)
						DrawScreen = false;
					else
						DrawScreen = true;
				}*/

				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					return 0;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					if (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift))
						ViewCentX -= 9;
					ViewCentX -= 1;
					view.setCenter(ViewCentX, ViewCentY);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					if (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift))
						ViewCentX += 9;
					ViewCentX += 1;
					view.setCenter(ViewCentX, ViewCentY);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					if (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift))
						ViewCentY -= 9;
					ViewCentY -= 1;
					view.setCenter(ViewCentX, ViewCentY);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					if (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift))
						ViewCentY += 9;
					ViewCentY += 1;
					view.setCenter(ViewCentX, ViewCentY);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Subtract)) {
					ViewZoom = 0.99;
					view.zoom(ViewZoom);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Add)) {
					ViewZoom = 1.01;
					view.zoom(ViewZoom);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Delete)) {
					for (i = 0; i < 3; i++) {
						PlayerInput[i] = "";
					}
					playerInput = "";
				}
			}
			if ((Mouse::isButtonPressed(Mouse::Left)) && MouseButtonPressd) {
				MouseButtonPressd = false;
				if (ButtonBul[0]) {
					s = PlayerInput[0];
					TemperatuteM = atof(s.c_str());
					playerInput = "";
					PlayerInput[0] = "";
					butoniter++;
				}else
				if (ButtonBul[1]) {
					s = PlayerInput[1];
					GameSpeed = atof(s.c_str());
					playerInput = "";
					PlayerInput[1] = "";
					butoniter++;
				}else
					if (ButtonBul[2]) {
						s = PlayerInput[2];
						soil = atof(s.c_str());
						playerInput = "";
						PlayerInput[2] = "";
						butoniter++;
					}
					else
				if (FieldBool[0]) {
					for (i = 0; i < 3; i++) {
						FieldWrite[i] = false;
					}
					FieldWrite[0] = true;
					butoniter++;
				}else
					if (FieldBool[1]) {
						for (i = 0; i < 3; i++) {
							FieldWrite[i] = false;
						}
						FieldWrite[1] = true;
						butoniter++;
					}
				else
					if (FieldBool[2]) {
					for (i = 0; i < 3; i++) {
						FieldWrite[i] = false;
					}
						FieldWrite[2] = true;
						butoniter++;
					}
			}
			if (!(Mouse::isButtonPressed(Mouse::Left))) {
				MouseButtonPressd = true;
			}
			for (i = 0; i <= SizeMapConst - 2; i++) {
				for (j = 0; j < SizeMapConst - 2; j++) {
					if (Map[i][j] == 1) {
						WallSprite.setPosition(i * 32, j * 32);
						window.draw(WallSprite);
					}
					if (Map[i][j] == 0) {
						FloorSprite.setPosition(i * 32, j * 32);
						window.draw(FloorSprite);
					}

				}
			}

			for (i = 0; i <= SizeMapConst - 2; i++) {
				for (j = 0; j < SizeMapConst - 2; j++) {
					if (FoodMap[i][j] == 1) {
						FoodSprite1.setPosition(i * 32, j * 32);
						window.draw(FoodSprite1);
					}
					else if (FoodMap[i][j] == 3) {
						FoodSprite3.setPosition(i * 32, j * 32);
						window.draw(FoodSprite3);
					}

				}
			}

			for (i = 0; i <= SizeMapConst - 2; i++) {
				for (j = 0; j < SizeMapConst - 2; j++) {
					if (ItemMap[i][j] == 2) {
						UnitSprite1.setPosition(i * 32, j * 32);
						window.draw(UnitSprite1);
					}

				}
			}











			TpsTimer += ((double)t1 / CLOCKS_PER_SEC - (double)t2 / CLOCKS_PER_SEC);

			t2 = t1;
			if (TpsTimer > 1) {
				TpsTimer = 0;
				//cout << "fps: " << IterCounter << endl;
				tps = IterCounter;
				IterCounter = 0;
			}
			window.setView(MenuView);
			window.draw(BorderW);
			BorderH.setPosition(350, 0);
			window.draw(BorderH);
			BorderH.setPosition(350, 145);
			window.draw(BorderH);
			BorderH.setPosition(350, 375);
			window.draw(BorderH);

			{
				buttonPosx = 600;
				buttonPosy = 190;
				if (Mouse::getPosition(window).x >= 648 + buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 680 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
					ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
					ButtonBul[0] = true;
					window.draw(ButtonSprite[0]);
				}
				else {
					ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
					ButtonBul[0] = false;
					window.draw(ButtonSprite[1]);
				}
				if (Mouse::getPosition(window).x >= buttonPosx + 448 && Mouse::getPosition(window).x <= buttonPosx + 628 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
					FieldBool[0] = true;
				}
				else {
					FieldBool[0] = false;
				}
				tana.setPosition(buttonPosx - 200, buttonPosy + 1);
				window.draw(tana);
				playerText.setFillColor(Color::Black);
				playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
				playerText.setString(PlayerInput[0]);
				window.draw(playerText);
			}
			{
				buttonPosx = 600;
				buttonPosy = 260;
				if (Mouse::getPosition(window).x >= 648 + buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 680 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
					ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
					ButtonBul[1] = true;
					window.draw(ButtonSprite[0]);
				}
				else {
					ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
					ButtonBul[1] = false;
					window.draw(ButtonSprite[1]);
				}
				if (Mouse::getPosition(window).x >= buttonPosx + 448 && Mouse::getPosition(window).x <= buttonPosx + 628 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
					FieldBool[1] = true;
				}
				else {
					FieldBool[1] = false;
				}
				tana.setPosition(buttonPosx - 200, buttonPosy + 1);
				window.draw(tana);
				playerText.setFillColor(Color::Black);
				playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
				playerText.setString(PlayerInput[1]);
				window.draw(playerText);
			}
			{
				buttonPosx = 600;
				buttonPosy = 330;
				if (Mouse::getPosition(window).x >= 648 + buttonPosx && Mouse::getPosition(window).x <= buttonPosx + 680 && Mouse::getPosition(window).y >= buttonPosy && Mouse::getPosition(window).y <= buttonPosy + 32) {
					ButtonSprite[0].setPosition(buttonPosx, buttonPosy);
					ButtonBul[2] = true;
					window.draw(ButtonSprite[0]);
				}
				else {
					ButtonSprite[1].setPosition(buttonPosx, buttonPosy);
					ButtonBul[2] = false;
					window.draw(ButtonSprite[1]);
				}
				if (Mouse::getPosition(window).x >= buttonPosx + 448 && Mouse::getPosition(window).x <= buttonPosx + 628 && Mouse::getPosition(window).y >= buttonPosy + 1 && Mouse::getPosition(window).y <= buttonPosy + 31) {
					FieldBool[2] = true;
				}
				else {
					FieldBool[2] = false;
				}
				tana.setPosition(buttonPosx - 200, buttonPosy + 1);
				window.draw(tana);
				playerText.setFillColor(Color::Black);
				playerText.setPosition(buttonPosx - 190, buttonPosy + 1);
				playerText.setString(PlayerInput[2]);
				window.draw(playerText);
			}

			text.setFillColor(Color::White);
			/*text.setString("x: " + to_string(MouseButtonPressd));
			text.setPosition(400, 500);
			window.draw(text);
			text.setString("x: " + to_string(butoniter));
			text.setPosition(400, 550);
			window.draw(text);


			text.setString("x: " + to_string(Mouse::getPosition(window).x));
			text.setPosition(400, 450);
			window.draw(text);
			text.setString("y: " + to_string(Mouse::getPosition(window).y));
			text.setPosition(400, 400);
			window.draw(text);*/



			s = "Tps: " + to_string(tps);
			text.setString(s);
			text.setPosition(400, 10);
			window.draw(text);
			
			text.setString("Units: " + to_string(UnitNum ));
			text.setPosition(400, 60);
			window.draw(text);

			text.setString("Food: " + to_string(FoodCurent));
			text.setPosition(400, 110);
			window.draw(text);

			text.setString("Temperature: " + to_string(TemperatuteM));
			text.setPosition(400, 160);
			window.draw(text);

			text.setString("Game speed: " + to_string(GameSpeed));
			text.setPosition(400, 230);
			window.draw(text);

			text.setString("Soil fertility: " + to_string(soil));
			text.setPosition(400, 300);
			window.draw(text);


			window.display();
		}
		});

int main() {
	

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return 0;
}