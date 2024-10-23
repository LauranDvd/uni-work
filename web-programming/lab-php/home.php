<!DOCTYPE html>
<html>

<head>
    <title>News</title>
    <link rel="stylesheet" href="style.css">
    <script type="text/javascript" src="javascript/jquery-3.7.1.min.js"></script>
    <script type="text/javascript" src="javascript/home_script.js"></script>
</head>

<body>
    <header>
        News Service
    </header>

    <section id="about-me">
        My name: <span id="my-name-span">-</span> <br />
        Am I admin?: <span id="am-i-admin-span">-</span> <br />
        <form action="do_logout.php">
            <input type="submit" value="logout, go to login page">
        </form>
    </section>
    Previous searched category: <span id="previous-category">-</span><br/>
    Previous start date: <span id="previous-startdate">-</span><br/>
    Previous end date: <span id="previous-enddate">-</span><br/><br/>

    Choose category:
    <select name="category-filter-select" id="category-filter-select">
    </select>
    <br />

    Choose start date:
    <input type="date" id="start-date-filter-input" value="2000-01-01">
    <br />

    Choose end date:
    <input type="date" id="end-date-filter-input" value="2050-12-12">
    <br />

    <section id="all-articles">
        <!-- <article class="news-article">
            <div class="news-article-title">
                The effect of the inflation on the prices of books
            </div>
            <div class="news-article-author">
                C.T.P.
            </div>
            <div class="news-article-text">
                What is the effect of the inflation what could the inflation do with
                the effect of the inflation what could the inflation do with
                the effect of the inflation what could the inflation do with
                the effect of the inflation what could the inflation do with
            </div>
            <div class="news-article-footer">
                <span class="news-article-date">5.6.2024</span> |
                <span class="news-article-category">politics</span>
            </div>
        </article>
        <article class="news-article">
            <div class="news-article-title">
                How we will begin to imagine earth
            </div>
            <div class="news-article-author">
                Florentina Gheorghidiu
            </div>
            <div class="news-article-text">
                Earth is green earth is round earth is something we should
                preoccupy our minds with because
                the effect of the inflation what could the inflation do with
                the effect of the inflation what could the inflation do with
            </div>
            <div class="news-article-footer">
                <span class="news-article-date">2.6.2024</span> |
                <span class="news-article-category">society</span>
            </div>
        </article> -->
    </section>

</body>

</html>