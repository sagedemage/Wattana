#include <array>
#include <iostream>
#include <stdexcept>

constexpr unsigned int LEVEL_WIDTH = 750;
constexpr unsigned int LEVEL_HEIGHT = 500;

void PlayerBoundary(sf::Vector2f *position, sf::FloatRect local_bounds);

int main() {
    const int player_width = 20;
    const int player_height = 20;
    const float speed = 2.F;
    const std::string player_image_file_path = "assets/art/player.png";
    const std::string music_file_path = "assets/music/hollow.ogg";

    // window
    sf::RenderWindow window(sf::VideoMode(LEVEL_WIDTH, LEVEL_HEIGHT),
                            "Wattana");

    window.setFramerateLimit(60);

    // player
    sf::RectangleShape player(sf::Vector2f(player_width, player_height));

    sf::Texture player_texture;
    if (!player_texture.loadFromFile(player_image_file_path)) {
        return -1;
    }

    player.setTexture(&player_texture);

    sf::Music music;
    if (!music.openFromFile(music_file_path)) {
        return -1;
    }

    const int volume = 50;
    music.setVolume(volume);

    music.setLoop(true);
    music.play();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
                default:
                    break;
            }
        }

        // Hold Keybindings
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            // move player left
            player.move(-speed, 0.F);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            // move player right
            player.move(speed, 0.F);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            // move player up
            player.move(0.F, -speed);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            // move player down
            player.move(0.F, speed);
        }

        // Player Boundary
        sf::Vector2f player_position = player.getPosition();
        PlayerBoundary(&player_position, player.getLocalBounds());
        player.setPosition(player_position);

        // set background color of the window
        window.clear(sf::Color(84, 193, 255, 255));
        window.draw(player);
        window.display();
    }

    return 0;
}

void PlayerBoundary(sf::Vector2f *position, sf::FloatRect local_bounds) {
    float width = local_bounds.width;
    float height = local_bounds.height;
    if (position->x + width >= 500.F) {
        /* Right boundary */
        position->x = static_cast<float>(500 - width);
    } else if (position->x <= 0.F) {
        /* Left  boundary */
        position->x = 0.F;
    }
    if (position->y <= 0.F) {
        /* Top boudnary */
        position->y = 0.F;
    } else if (position->y + height >= 500) {
        /* Bottom boudnary */
        position->y = static_cast<float>(500 - height);
    }
}
