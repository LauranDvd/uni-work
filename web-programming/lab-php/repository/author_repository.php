<?php
class AuthorRepository
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

    public function getById($authorId)
    {
        // $queryResult = mysqli_query(
        //     $this->dbConnection,
        //     "SELECT * FROM the_authors WHERE authorId=" . $authorId
        // );
        // $firstRow = mysqli_fetch_array($queryResult);
        // return $firstRow;

        $selectQuery = $this->dbConnection->prepare("SELECT * FROM the_authors WHERE authorId=?");
        $selectQuery->bind_param("i", $authorId);
        $selectQuery->execute();
        $result = $selectQuery->get_result();
        return $result->fetch_array(MYSQLI_ASSOC);
    }

    public function getByName($authorName)
    {
        // $queryResult = mysqli_query(
        //     $this->dbConnection,
        //     "SELECT * FROM the_authors WHERE authorName='" . $authorName . "'"
        // );
        // $firstRow = mysqli_fetch_array($queryResult);
        // return $firstRow;

        $selectQuery = $this->dbConnection->prepare("SELECT * FROM the_authors WHERE authorName=?");
        $selectQuery->bind_param("s", $authorName);
        $selectQuery->execute();
        $result = $selectQuery->get_result();
        return $result->fetch_array(MYSQLI_ASSOC);
    }

    public function add($authorName)
    {
        // $insertQuery = "INSERT INTO the_authors (authorName) VALUES ('" . $authorName . "')";
        // mysqli_query($this->dbConnection, $insertQuery);

        $insertQuery = $this->dbConnection->prepare("INSERT INTO the_authors (authorName) VALUES (?)");
        $insertQuery->bind_param("s", $authorName);
        $insertQuery->execute();
    }
}
