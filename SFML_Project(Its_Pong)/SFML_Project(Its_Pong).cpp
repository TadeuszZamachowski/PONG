#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Ball.h"

constexpr unsigned WIDTH = 1024;
constexpr unsigned HEIGHT = 768;
constexpr unsigned PLAYER_WIDTH = 20;
constexpr unsigned PLAYER_HEIGHT = 100;

class Game {
public:
    Game() 
        : window(sf::VideoMode(WIDTH, HEIGHT), "PONG"),
          player1(10, (HEIGHT - PLAYER_HEIGHT) / 2),
          player2(WIDTH - 30, (HEIGHT - PLAYER_HEIGHT) / 2),
          ball(WIDTH / 2, HEIGHT / 2) {
        initializeUI();
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

private:
    enum class GameState {
        Playing,
        GameOver,
        Paused
    };

    sf::RenderWindow window;
    Player player1;
    Player player2;
    Ball ball;
    GameState state = GameState::Paused;

    // UI elements
    sf::Font font;
    sf::Text p1Hud;
    sf::Text p2Hud;
    sf::Text gameOverText;

    void initializeUI() {
        if (!font.loadFromFile("ARCADECLASSIC.TTF")) {
            // Handle font loading error
        }

        p1Hud.setFont(font);
        p1Hud.setCharacterSize(70);
        p1Hud.setFillColor(sf::Color::White);
        p1Hud.setPosition(30, 0);

        p2Hud.setFont(font);
        p2Hud.setCharacterSize(70);
        p2Hud.setFillColor(sf::Color::White);
        p2Hud.setPosition(WIDTH - 70, 0);  // Adjusted for better positioning

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(70);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(WIDTH / 4, HEIGHT / 3);
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code);
            }
        }
    }

    void handleKeyPress(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Space) {
            if (state == GameState::GameOver) {
                resetGame();
            }
            state = (state == GameState::Paused) ? GameState::Playing : GameState::Paused;
        }
    }

    void update() {
        if (state != GameState::Playing) return;

        updatePlayers();
        updateBall();
        updateHUD();
        checkGameOver();
    }

    void updatePlayers() {
        player1.handleInput(false);
        player1.checkBounds(HEIGHT);

        player2.handleInput(true);
        player2.checkBounds(HEIGHT);
    }

    void updateBall() {
        ball.bounceFromWall(HEIGHT);
        ball.bounceFromPlayer(player1);
        ball.bounceFromPlayer(player2);

        if (ball.outOfBounds(WIDTH, HEIGHT)) {
            handlePointScored();
            ball.resetPosition(WIDTH, HEIGHT);
            state = GameState::Paused;
        }

        ball.updatePosition();
    }

    void handlePointScored() {
        if (ball.getPosition().left > WIDTH) {
            player1.incrementPoints();
        }
        else {
            player2.incrementPoints();
        }
    }

    void updateHUD() {
        p1Hud.setString(std::to_string(player1.getPoints()));
        p2Hud.setString(std::to_string(player2.getPoints()));
    }

    void checkGameOver() {
        const int WINNING_SCORE = 2;
        if (player1.getPoints() >= WINNING_SCORE || player2.getPoints() >= WINNING_SCORE) {
            state = GameState::GameOver;
            updateGameOverText();
        }
    }

    void updateGameOverText() {
        std::string winner = (player1.getPoints() > player2.getPoints()) ? "PLAYER 1" : "PLAYER 2";
        std::string message = "GAME OVER\n" + winner + " WINS!\nPRESS SPACE TO RESTART";
        gameOverText.setString(message);
        
        // Center the text
        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
        gameOverText.setPosition(WIDTH / 2, HEIGHT / 3);
    }

    void resetGame() {
        player1.resetPoints();
        player2.resetPoints();
        ball.resetPosition(WIDTH, HEIGHT);
        state = GameState::Paused;
    }

    void render() {
        window.clear();
        
        // Draw game objects
        window.draw(player1.getShape());
        window.draw(player2.getShape());
        if (state != GameState::GameOver) {
            window.draw(ball.getShape());
        }
        
        // Draw UI
        window.draw(p1Hud);
        window.draw(p2Hud);
        
        if (state == GameState::GameOver) {
            window.draw(gameOverText);
        }
        
        window.display();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
