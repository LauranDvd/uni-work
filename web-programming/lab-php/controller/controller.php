<?php
header('Access-Control-Allow-Origin: *');

require_once '../model/model.php';
require_once '../model/entity/article.php';


class Controller
{
    private $model;

    public function __construct()
    {
        $this->model = new Model();
    }

    public function service()
    {
        if (isset($_GET['action']) && !empty($_GET['action'])) {
            switch ($_GET['action']) {
                case 'loadArticles':
                    echo json_encode($this->loadArticles($_GET['category'], $_GET['startDate'], $_GET['endDate']));
                    break;
                case 'getAllCategories':
                    echo json_encode($this->getAllCategories());
                    break;
                case 'getMyNameAndAdminStatus':
                    echo json_encode($this->getMyNameAndAdminStatus());
                    break;
                case 'getArticleById':
                    echo json_encode($this->getArticleById($_GET['articleId']));
                    break;
            }
        }

        if (isset($_POST['action']) && !empty($_POST['action'])) {
            // only admins can send these requests
            $nameAndAdminStatus = $this->getMyNameAndAdminStatus();
            if ($nameAndAdminStatus != null && $nameAndAdminStatus["adminStatus"]) {
                switch ($_POST['action']) {
                    case 'postNewArticle':
                        $this->postArticle(
                            $_POST['title'],
                            $_POST['text'],
                            $_POST['author'],
                            $_POST['category'],
                            $_POST['date']
                        );
                        break;
                    case 'updateArticle':
                        $this->updateArticle(
                            $_POST['id'],
                            $_POST['title'],
                            $_POST['text'],
                            $_POST['author'],
                            $_POST['category'],
                            $_POST['date']
                        );
                        break;
                    case 'deleteArticle':
                        $this->deleteArticle($_POST['articleId']);
                        break;
                }
            } else {
                echo json_encode('error: you are not an admin');
            }
        }
    }

    private function loadArticles($category, $startDate, $endDate)
    {
        if (!($this->existsCategoryName($category)))
            return array();

        return $this->model->getAllArticles($category, $startDate, $endDate);
    }

    private function existsCategoryName($soughtCategoryName)
    {
        foreach ($this->getAllCategories() as $category) {
            if ($category['categoryName'] == $soughtCategoryName)
                return true;
        }
        return false;
    }

    private function getAllCategories()
    {
        return $this->model->getAllCategories();
    }

    private function getMyNameAndAdminStatus()
    {
        if (!isset($_SESSION['userId'])) {
            return null;
        }
        return [
            "name" => $this->model->getUserFullNameById($_SESSION['userId']),
            "adminStatus" => $this->model->getUserIsAdminById($_SESSION['userId'])
        ];
    }

    private function getArticleById($articleId)
    {
        if (!is_numeric($articleId))
            return null;

        return $this->model->getArticleById($articleId);
    }

    private function postArticle($title, $text, $author, $category, $date)
    {
        $errors = $this->validateArticle($title, $text, $author, $category, $date);

        if ($errors == "")
            $this->model->postArticle($title, $text, $author, $category, $date);
        echo json_encode($errors);
    }

    private function validateArticle($title, $text, $author, $category, $date)
    {
        $errors = "";

        if ($title == "")
            $errors = $errors . "title is empty; ";
        if (strlen($text) < 3)
            $errors = $errors . "text should have at least 3 characters; ";
        if ($author == "")
            $errors = $errors . "author is empty; ";
        if ($category == "")
            $errors = $errors . "category is empty; ";
        if ($date < "1000-01-01")
            $errors = $errors . "date is too early; ";
        if ($date > "2500-12-12")
            $errors = $errors . "date is too late; ";

        return $errors;
    }

    private function updateArticle($id, $title, $text, $author, $category, $date)
    {
        if ($this->getArticleById($id) == null) {
            echo json_encode('You tried to update an article with an invalid id');
            return;
        }

        $errors = $this->validateArticle($title, $text, $author, $category, $date);

        if ($errors == "")
            $this->model->updateArticle($id, $title, $text, $author, $category, $date);
        echo json_encode($errors);
    }

    private function deleteArticle($articleId)
    {
        if ($this->getArticleById($articleId) == null) {
            echo json_encode('You tried to delete an article with an invalid id');
            return;
        }

        $this->model->deleteArticle($articleId);
    }
}

session_start();
$controller = new Controller();
$controller->service();
