package ui.widgets;

import game.Croco;
import game.Fruit;
import game.Game;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Tab;
import javafx.scene.image.Image;
import javafx.scene.layout.Pane;
import javafx.util.Duration;

import java.util.ArrayList;
import java.util.List;

public class ClientTab extends Tab {

    private String name;
    private Pane pane;
    private GameView gameView;
    private String gameId;
    private Timeline killer;
    private List<Croco> crocos = new ArrayList<>();
    private List<Fruit> fruits = new ArrayList<>();

    public ClientTab(String name) {
        this.name = name;
        this.pane = new Pane();
    }

    public void load() {
        setText(name);
        loadSpawners();
        loadGameView();
        loadAutoButton();
        setContent(pane);
        startKiller();
    }

    public void updateGameView(Game game) {
        gameView.update(game);

        if (killer != null) killer.stop();
        startKiller();
    }

    private void close() {
        this.getTabPane().getTabs().remove(this);
    }

    private void loadAutoButton() {
        RadioButton radioButton = new RadioButton("Auto");
        radioButton.relocate(900, 680);
        radioButton.setOnMousePressed(
                event -> autoButtonPressed(!radioButton.selectedProperty().getValue()));

        pane.getChildren().add(radioButton);
    }

    private void loadGameView() {
        gameView = new GameView(660, 460);
        gameView.relocate(310, 100);
        gameView.load();

        pane.getChildren().add(gameView);
    }

    private void loadSpawners() {
        Image crocoIcon = new Image("croco.png");
        Spawner croco = new Spawner(crocoIcon);
        croco.relocate(100, 600);
        croco.setClientTab(this);
        croco.setType("croco");
        croco.load();

        Image fruitIcon = new Image("fruit.png");
        Spawner fruit = new Spawner(fruitIcon);
        fruit.relocate(100, 720);
        fruit.setClientTab(this);
        fruit.setType("fruit");
        fruit.load();

        pane.getChildren().addAll(croco, fruit);
    }

    private void startKiller() {
        killer = new Timeline(new KeyFrame(
                Duration.seconds(5),
                e -> close()));
        killer.play();
    }

    private void autoButtonPressed(Boolean selected) {
        System.out.println(selected);
    }

    public GameView getGameView() {
        return gameView;
    }

    public String getGameId() {
        return gameId;
    }

    public void setGameId(String gameId) {
        this.gameId = gameId;
    }

    public List<Croco> getCrocos() {
        return crocos;
    }

    public void setCrocos(List<Croco> crocos) {
        this.crocos = crocos;
    }

    public List<Fruit> getFruits() {
        return fruits;
    }

    public void setFruits(List<Fruit> fruits) {
        this.fruits = fruits;
    }
}
