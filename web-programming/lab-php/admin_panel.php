<?php
require_once 'repository/user_repository.php';

session_start();
if (!isset($_SESSION['userId']))
    header('Location: home.php');

$userRepository = new UserRepository();
if (!($userRepository->getById($_SESSION['userId']))['userIsAdmin'])
    header('Location: home.php');
?>

<!DOCTYPE html>
<html>

<head>
    <title>News</title>
    <link rel="stylesheet" href="style.css">
    <script type="text/javascript" src="javascript/jquery-3.7.1.min.js"></script>
    <script type="text/javascript" src="javascript/admin_panel_script.js"></script>
</head>

<body>
    <header>
        News Service - admin panel
    </header>

    <section id="about-me">
        My name: <span id="my-name-span">-</span> <br />
        Am I admin?: <span id="am-i-admin-span">-</span> <br />
        <form action="do_logout.php">
            <input type="submit" value="logout, go to login page">
        </form>
    </section>

    <section id="article-inputs-section">
        <input type="text" placeholder="title" name="title-input" id="title-input"> <br />
        <textarea placeholder="text" name="text-input" id="text-input"></textarea> <br />
        <input type="text" placeholder="author" name="author-input" id="author-input"> <br />
        <input type="text" placeholder="category" name="category-input" id="category-input"> <br />
        <label for="date-input">Date: </label>
        <input type="date" name="date-input" id="date-input"> <br />
        <button id="post-new-article-submit-button">Post</button> <br />
        <span>Note: if the category or the author doesn't exist yet, it will be created.</span>
    </section>

</body>

</html>