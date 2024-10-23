<?php
class ArticleRepository
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

    public function getAll()
    {
        $articles = array();

        $result = mysqli_query($this->dbConnection, "SELECT * FROM articles");
        while ($row = mysqli_fetch_array($result)) {
            // $oneArticle = array();
            // $oneArticle['articleTitle'] = $row['articleTitle'];
            // $oneArticle['author'] = $this->getAuthorNameById($row['authorId']);
            // $oneArticle['articleText'] = $row['articleText'];
            // $oneArticle['articleDate'] = $row['articleDate'];
            // $oneArticle['category'] = $this->getCategoryNameById($row['categoryId']);

            $articles[] = $row;
        }

        return $articles;
    }

    public function getById($articleId)
    {
        // $queryResult = mysqli_query(
        //     $this->dbConnection,
        //     "SELECT * FROM articles WHERE articleId=" . $articleId
        // );
        // $firstRow = mysqli_fetch_array($queryResult);
        // return $firstRow;

        $selectQuery = $this->dbConnection->prepare("SELECT * FROM articles WHERE articleId=?");
        $selectQuery->bind_param("i", $articleId);
        $selectQuery->execute();
        $result = $selectQuery->get_result();
        return $result->fetch_array(MYSQLI_ASSOC);
    }

    public function postArticle($title, $text, $authorId, $categoryId, $date)
    {
        // $insertQuery =
        //     "INSERT INTO articles (articleTitle, authorId, articleText, articleDate, categoryId) 
        //     VALUES ('" . $title . "', " . $authorId . ", '" . $text . "', '" . $date . "', " . $categoryId . ")";
        // mysqli_query($this->dbConnection, $insertQuery);

        $insertQuery = $this->dbConnection->prepare(
            "INSERT INTO articles (articleTitle, authorId, articleText, articleDate, categoryId) 
            VALUES (?, ?, ?, ?, ?)"
        );
        $insertQuery->bind_param("sissi", $title, $authorId, $text, $date, $categoryId);
        $insertQuery->execute();
    }

    public function updateArticle($id, $title, $text, $authorId, $categoryId, $date)
    {
        // $updateQuery = "UPDATE articles SET articleTitle='" . $title . "', articleText='" . $text . "', authorId=" . $authorId .
        //     ", categoryId=" . $categoryId . ", articleDate='" . $date . "' WHERE articleId=" . $id;
        // mysqli_query($this->dbConnection, $updateQuery);

        $updateQuery = $this->dbConnection->prepare(
            "UPDATE articles SET articleTitle=?, articleText=?, authorId=?, 
            categoryId=?, articleDate=? WHERE articleId=?"
        );
        $updateQuery->bind_param("ssiisi", $title, $text, $authorId, $categoryId, $date, $id);
        $updateQuery->execute();
    }

    public function deleteById($articleId)
    {
        // $deleteQuery = "DELETE FROM articles WHERE articleId=" . $articleId;
        // mysqli_query($this->dbConnection, $deleteQuery);

        $deleteQuery = $this->dbConnection->prepare("DELETE FROM articles WHERE articleId=?");
        $deleteQuery->bind_param("i", $articleId);
        $deleteQuery->execute();
    }
}
