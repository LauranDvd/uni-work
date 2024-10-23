<?php
class CategoryRepository
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

    public function getAllCategoryNames()
    {
        $categories = array();

        $result = mysqli_query($this->dbConnection, "SELECT * FROM categories");
        while ($row = mysqli_fetch_array($result)) {
            $oneCategory = array();
            $oneCategory['categoryName'] = $row['categoryName'];

            $categories[] = $oneCategory;
        }

        return $categories;
    }

    public function getById($categoryId)
    {
        // $queryResult = mysqli_query(
        //     $this->dbConnection,
        //     "SELECT * FROM categories WHERE categoryId=" . $categoryId
        // );
        // $firstRow = mysqli_fetch_array($queryResult);
        // return $firstRow;

        $selectQuery = $this->dbConnection->prepare("SELECT * FROM categories WHERE categoryId=?");
        $selectQuery->bind_param("i", $categoryId);
        $selectQuery->execute();
        $result = $selectQuery->get_result();
        return $result->fetch_array(MYSQLI_ASSOC);
    }

    public function getByName($categoryName)
    {
        // $queryResult = mysqli_query(
        //     $this->dbConnection,
        //     "SELECT * FROM categories WHERE categoryName='" . $categoryName . "'"
        // );
        // $firstRow = mysqli_fetch_array($queryResult);
        // return $firstRow;

        $selectQuery = $this->dbConnection->prepare("SELECT * FROM categories WHERE categoryName=?");
        $selectQuery->bind_param("s", $categoryName);
        $selectQuery->execute();
        $result = $selectQuery->get_result();
        return $result->fetch_array(MYSQLI_ASSOC);
    }

    public function add($categoryName)
    {
        // $insertQuery = "INSERT INTO categories (categoryName) VALUES ('" . $categoryName . "')";
        // mysqli_query($this->dbConnection, $insertQuery);

        $insertQuery = $this->dbConnection->prepare("INSERT INTO categories (categoryName) VALUES (?)");
        $insertQuery->bind_param("s", $categoryName);
        $insertQuery->execute();
    }
}
