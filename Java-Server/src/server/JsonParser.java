package server;
import game.Croco;
import game.Fruit;
import game.Game;
import org.json.JSONArray;
import org.json.JSONObject;
import ui.ClientTabManager;
import ui.widgets.ClientTab;


class JsonParser {

    static Integer parseGame(String json) {
        Game game = new Game();
        game.parse(json);
        ClientTabManager.createTab(game);
        return game.getId();
    }

    static String serializeGame(Integer gameId) {
        ClientTab clientTab = ClientTabManager.searchClientTab(gameId);
        if (clientTab == null) return "";

        JSONArray crocosArray = new JSONArray();
        for (Croco croco : clientTab.getCrocos()) {
            crocosArray.put(croco.serialize());
        }

        JSONArray fruitsArray = new JSONArray();
        for (Fruit fruit : clientTab.getFruits()) {
            fruitsArray.put(fruit.serialize());
        }

        JSONObject jsonObject = new JSONObject();
        jsonObject.put("crocos", crocosArray);
        jsonObject.put("fruits", fruitsArray);

        return jsonObject.toString();
    }
}
