package webubb.domain;

/**
 * Created by forest.
 */
public class User {
    private int userId;
    private String username;
    private String userPassword;

    public User(int userId, String username, String userPassword) {
        this.userId = userId;
        this.username = username;
        this.userPassword = userPassword;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getUserPassword() {
        return userPassword;
    }

    public void setUserPassword(String userPassword) {
        this.userPassword = userPassword;
    }
}