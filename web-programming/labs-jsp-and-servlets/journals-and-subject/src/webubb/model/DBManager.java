package webubb.model;

import webubb.domain.Article;
import webubb.domain.Journal;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBManager {
    private static DBManager instance;
    private Statement statement;
    private Connection connection;

    private DBManager() {
        connect();
    }

    public static DBManager getInstance() {
        if (instance == null)
            instance = new DBManager();
        return instance;
    }

    private void connect() {
        try {
            Class.forName("org.gjt.mm.mysql.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/web_play", "david", "password");
            statement = connection.createStatement();
        } catch (Exception ex) {
            System.out.println("connect error :" + ex.getMessage());
            ex.printStackTrace();
        }
    }

//    public User authenticate(String username, String password) {
//        ResultSet rs;
//        User u = null;
//        System.out.println(username + " " + password);
//        try {
//            rs = statement.executeQuery(
//                    "select * from users where username='" + username + "' and userPassword='" + password + "'"
//            );
//            if (rs.next()) {
//                u = new User(rs.getInt("userId"), rs.getString("username"), rs.getString("userPassword"));
//            }
//            rs.close();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//        return u;
//    }

    public List<Article> getArticles(String journalName, String userName) {
        System.out.println("db manager will get pictures");
        List<Article> articles = new ArrayList<>();
        ResultSet rs;
        try {
//            rs = statement.executeQuery(
//                    "select P.pictureId, P.uploader, P.url, sum(UPV.score) as totalScore" +
//                            " from pictures P left join userspicturesvotes UPV on P.pictureId=UPV.pictureId " +
//                            "group by P.pictureId, P.uploader, P.url " +
//                            " order by totalScore DESC " +
//                            "limit " + journalName
//            );
            rs = statement.executeQuery(
                    "select A.id, A.user, J.name AS journalName, A.summary, A.date " +
                            "from articles A inner join journals J on A.journalId=J.id " +
                            "where J.name='" + journalName + "' and A.user='" + userName + "'"
            );

            while (rs.next()) {
                System.out.println("dbmanager got a article, id=" + rs.getInt("id"));
                articles.add(new Article(
                        rs.getInt("id"),
                        rs.getString("user"),
                        rs.getString("journalName"),
                        rs.getString("summary"),
                        rs.getString("date")
                ));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return articles;
    }

    public List<Article> getOthersArticlesSince(String date, String userName) {
        List<Article> articles = new ArrayList<>();
        ResultSet rs;
        try {
            rs = statement.executeQuery(
                    "select A.id, A.user, J.name AS journalName, A.summary, A.date " +
                            "from articles A inner join journals J on A.journalId=J.id  " +
                            "where date>='" + date + "' and A.user<>'" + userName + "'"
            );

            while (rs.next()) {
                System.out.println("dbmanager got a article, id=" + rs.getInt("id"));
                articles.add(new Article(
                        rs.getInt("id"),
                        rs.getString("user"),
                        rs.getString("journalName"),
                        rs.getString("summary"),
                        rs.getString("date")
                ));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return articles;
    }

    public Journal getJournalByName(String journalName) {
        ResultSet rs;
        Journal journal = null;
        try {
            rs = statement.executeQuery(
                    "select * " +
                            "from journals " +
                            "where name='" + journalName + "'"
            );

            if (rs.next()) {
                journal = new Journal(
                        rs.getInt("id"),
                        rs.getString("name")
                );
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return journal;
    }

    public void addJournal(String journalName) {
        try {
            String query = "insert into journals(name) values (?)";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, journalName);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void addArticle(String userName, int journalId, String summary, String dateTime) {
        try {
            String query = "insert into articles(user, journalId, summary, date) values (?, ?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, userName);
            statement.setInt(2, journalId);
            statement.setString(3, summary);
            statement.setString(4, dateTime);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}