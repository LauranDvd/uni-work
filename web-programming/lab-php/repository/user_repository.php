<?php
class UserRepository
{
    private $dbConnection;

    public function __construct()
    {
        $this->dbConnection = mysqli_connect("localhost", "david", "password", "news_service");
    }

    public function __destruct()
    {
        mysqli_close($this->dbConnection);
    }

    public function getByUsernamePassword($username, $password)
    {
        // BAD: inputting this in both fields makes you admin: 
        // ' or ''='
        // $result = mysqli_query(
        //     $this->dbConnection,
        //     "SELECT * FROM users WHERE username='" . $username . "' AND userPassword='" . $password . "'"
        // );
        // $row = mysqli_fetch_array($result);
        // return $row;

        $selectQuery = $this->dbConnection->prepare("SELECT * FROM users WHERE username=? AND userPassword=?");
        $selectQuery->bind_param("ss", $username, $password);
        $selectQuery->execute();
        $result = $selectQuery->get_result();
        return $result->fetch_array(MYSQLI_ASSOC);
    }

    public function getById($userId)
    {
        // $queryResult = mysqli_query(
        //     $this->dbConnection,
        //     "SELECT * FROM users WHERE userId=" . $userId
        // );
        // $firstRow = mysqli_fetch_array($queryResult);
        // return $firstRow;

        $selectQuery = $this->dbConnection->prepare("SELECT * FROM users WHERE userId=?");
        $selectQuery->bind_param("i", $userId);
        $selectQuery->execute();
        $result = $selectQuery->get_result();
        return $result->fetch_array(MYSQLI_ASSOC);
    }
}
