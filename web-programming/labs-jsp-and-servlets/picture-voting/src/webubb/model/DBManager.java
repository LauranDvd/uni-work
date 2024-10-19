package webubb.model;

import webubb.domain.Picture;
import webubb.domain.User;

import java.sql.*;
import java.util.ArrayList;

public class DBManager {
    private Statement statement;
    private Connection connection;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("org.gjt.mm.mysql.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/pics_app", "david", "password");
            statement = connection.createStatement();
        } catch (Exception ex) {
            System.out.println("connect error :" + ex.getMessage());
            ex.printStackTrace();
        }
    }

    public User authenticate(String username, String password) {
        ResultSet rs;
        User u = null;
        System.out.println(username + " " + password);
        try {
            rs = statement.executeQuery(
                    "select * from users where username='" + username + "' and userPassword='" + password + "'"
            );
            if (rs.next()) {
                u = new User(rs.getInt("userId"), rs.getString("username"), rs.getString("userPassword"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public ArrayList<Picture> getPictures(int noPicsToLoad) {
        System.out.println("db manager will get pictures");
        ArrayList<Picture> pictures = new ArrayList<>();
        ResultSet rs;
        try {
            rs = statement.executeQuery(
                    "select P.pictureId, P.uploader, P.url, sum(UPV.score) as totalScore" +
                            " from pictures P left join userspicturesvotes UPV on P.pictureId=UPV.pictureId " +
                            "group by P.pictureId, P.uploader, P.url " +
                            " order by totalScore DESC " +
                            "limit " + noPicsToLoad
            );
            while (rs.next()) {
                System.out.println("dbmanager got a picture, id=" + rs.getInt("pictureId"));
                pictures.add(new Picture(
                        rs.getInt("pictureId"),
                        rs.getInt("uploader"),
                        rs.getString("url")
                ));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return pictures;
    }

    public void savePicture(int userId, String pictureUrl) {
        System.out.println("we in savepictures in dbmanager");
        try {
            String query = "insert into pictures(uploader, url) values (?, ?)";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setInt(1, userId);
            statement.setString(2, pictureUrl);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public int getUsersVote(int userId, int pictureId) {
        System.out.println("db manager will get users vote");

        int vote = -1;
        ResultSet rs;
        try {
            rs = statement.executeQuery("select score from userspicturesvotes where userId=" + userId + " and pictureId=" + pictureId);
            if (rs.next()) {
                vote = rs.getInt("score");
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return vote;
    }

    public void votePicture(int userId, int pictureId, int score) {
        System.out.println("we in votePicture in dbmanager");

        if (getUserIdOfPicture(pictureId) == userId) {
            System.out.println("dbmanager: trying to vote own photo");
            return;
        }

        try {
            String query = "insert into userspicturesvotes(userId, pictureId, score) values (?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setInt(1, userId);
            statement.setInt(2, pictureId);
            statement.setInt(3, score);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private int getUserIdOfPicture(int pictureId) {
        int userId = 0;
        ResultSet rs;
        try {
            rs = statement.executeQuery("select uploader from pictures where pictureId=" + pictureId);
            if (rs.next()) {
                userId = rs.getInt("uploader");
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return userId;
    }

    public int getTotalScoreOfPicture(int pictureId) {
        System.out.println("db manager will get total score of a picture");

        int score = 0;
        ResultSet rs;
        try {
            rs = statement.executeQuery("select sum(score) as totalScore from userspicturesvotes where pictureId=" + pictureId);
            if (rs.next()) {
                score = rs.getInt("totalScore");
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return score;
    }

    public String getUsernameById(int userId) {
        System.out.println("db manager will get username by id");

        String username = "";
        ResultSet rs;
        try {
            rs = statement.executeQuery("select username from users where userId=" + userId);
            if (rs.next()) {
                username = rs.getString("username");
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return username;
    }
}