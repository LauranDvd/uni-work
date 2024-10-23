<?php
require_once '../repository/article_repository.php';
require_once '../repository/user_repository.php';
require_once '../repository/category_repository.php';
require_once '../repository/author_repository.php';

class Model
{
    private $articleRepository;
    private $userRepository;
    private $categoryRepository;
    private $authorRepository;

    public function __construct()
    {
        $this->articleRepository = new ArticleRepository();
        $this->userRepository = new UserRepository();
        $this->categoryRepository = new CategoryRepository();
        $this->authorRepository = new AuthorRepository();
    }

    public function getAllArticles($category, $startDate, $endDate)
    {
        $allArticles = $this->articleRepository->getAll();
        $allArticles = $this->changeAuthorIdCategoryIdToNames($allArticles);

        $allArticlesInCategory = array();
        foreach ($allArticles as $article) {
            if (
                $article['category'] == $category &&
                $article['articleDate'] >= $startDate && $article['articleDate'] <= $endDate
            )
                $allArticlesInCategory[] = $article;
        }
        return $allArticlesInCategory;
    }

    public function getAllCategories()
    {
        return $this->categoryRepository->getAllCategoryNames(); // TODO something?
    }

    public function getUserFullNameById($userId)
    {
        return ($this->userRepository->getById($userId))['userFullName'];
    }

    public function getNameAndAdminStatusByCredentials($username, $password)
    {
        $user = $this->userRepository->getByUsernamePassword($username, $password);
        if ($user == null)
            return null;

        $nameAndAdminStatus['fullname'] = $user['userFullName'];
        $nameAndAdminStatus['isAdmin'] = $user['userIsAdmin'];
        return $nameAndAdminStatus;
    }

    public function getUserIsAdminById($userId)
    {
        return ($this->userRepository->getById($userId))['userIsAdmin'];
    }

    public function getArticleById($articleId)
    {
        $article = $this->articleRepository->getById($articleId);
        $arrayWithArticle = array();
        $arrayWithArticle[] = $article;
        return $this->changeAuthorIdCategoryIdToNames($arrayWithArticle)[0];
    }

    public function postArticle($title, $text, $author, $category, $date)
    {
        if ($this->authorRepository->getByName($author) == null) {
            $this->authorRepository->add($author);
        }
        if ($this->categoryRepository->getByName($category) == null) {
            $this->categoryRepository->add($category);
        }

        $authorId = ($this->authorRepository->getByName($author))['authorId'];
        $categoryId = ($this->categoryRepository->getByName($category))['categoryId'];

        $this->articleRepository->postArticle($title, $text, $authorId, $categoryId, $date);
    }

    public function updateArticle($id, $title, $text, $author, $category, $date)
    {
        if ($this->authorRepository->getByName($author) == null) {
            $this->authorRepository->add($author);
        }
        if ($this->categoryRepository->getByName($category) == null) {
            $this->categoryRepository->add($category);
        }

        $authorId = ($this->authorRepository->getByName($author))['authorId'];
        $categoryId = ($this->categoryRepository->getByName($category))['categoryId'];

        $this->articleRepository->updateArticle($id, $title, $text, $authorId, $categoryId, $date);
    }

    public function deleteArticle($articleId)
    {
        $this->articleRepository->deleteById($articleId);
    }

    private function changeAuthorIdCategoryIdToNames($allArticles)
    {
        $allArticlesWithNames = array();
        foreach ($allArticles as $article) {
            $articleWithNames = array();
            $articleWithNames['articleTitle'] = $article['articleTitle'];
            $articleWithNames['articleId'] = $article['articleId'];
            $articleWithNames['author'] = $this->getAuthorNameById($article['authorId']);
            $articleWithNames['articleText'] = $article['articleText'];
            $articleWithNames['articleDate'] = $article['articleDate'];
            $articleWithNames['category'] = $this->getCategoryNameById($article['categoryId']);

            $allArticlesWithNames[] = $articleWithNames;
        }
        return $allArticlesWithNames;
    }

    private function getAuthorNameById($authorId)
    {
        return ($this->authorRepository->getById($authorId))['authorName'];
    }

    private function getCategoryNameById($categoryId)
    {
        // echo json_encode(($this->categoryRepository->getById($categoryId))['categoryName']);
        return ($this->categoryRepository->getById($categoryId))['categoryName'];
    }

    // public function getUserByUsername($username) {
    //     $userIn...Form = $this->userRepository->getByUsername($username);
    //     $user = new User(...);  // TODO!
    //     return $user;
    // }


}
