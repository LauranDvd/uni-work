let previousCategory = "-";
let previousStartDate = "-";
let previousEndDate = "-";

$(document).ready(function () {
    // loadArticles();

    populateAboutMeSection();

    populateCategorySelect();

    $("#category-filter-select").on('change', loadArticlesBasedOnInputs);
    $("#start-date-filter-input").on('change', loadArticlesBasedOnInputs);
    $("#end-date-filter-input").on('change', loadArticlesBasedOnInputs);

    $("#start-date-filter-input").on('focusout', validateDate);
    $("#end-date-filter-input").on('focusout', validateDate);
});

function populateAboutMeSection() {
    $.getJSON(
        "controller/controller.php",
        { action: "getMyNameAndAdminStatus" },
        function (nameAndAdminStatus) {
            // TODO if?
            $("#my-name-span").html(nameAndAdminStatus['name']);
            $("#am-i-admin-span").html(nameAndAdminStatus['adminStatus'] == 1 ? "yes" : "no");

            if (nameAndAdminStatus['adminStatus']) {
                let adminPanelElement = $('<a></a>');
                adminPanelElement.attr('href', 'admin_panel.php');
                adminPanelElement.html('Go to admin panel');
                $("#am-i-admin-span")
                    .append("<br />")
                    .append(adminPanelElement);
            }
        }
    );
}

function populateCategorySelect() {
    $.getJSON(
        "controller/controller.php",
        { action: "getAllCategories" },
        function (allCategories) {
            console.log('controller returned the following categories: ' + JSON.stringify(allCategories));
            allCategories.forEach(category => {
                let categoryName = category['categoryName'];
                let optionElement = $('<option></option>')
                    .val(categoryName)
                    .append(categoryName);
                $("#category-filter-select").append(optionElement);
            });
        }
    );
}

function loadArticlesBasedOnInputs() {
    $("#previous-category").html(previousCategory);
    $("#previous-startdate").html(previousStartDate);
    $("#previous-enddate").html(previousEndDate);
    previousCategory = $("#category-filter-select option:selected").val();
    previousStartDate = $("#start-date-filter-input").val();
    previousEndDate = $("#end-date-filter-input").val();
    
    console.log('load on inputs now');
    loadArticles(
        $("#category-filter-select option:selected").val(),
        $("#start-date-filter-input").val(),
        $("#end-date-filter-input").val()
    );
}

function loadArticles(categoryToLoad, startDateToLoad, endDateToLoad) {
    $.getJSON(
        "controller/controller.php",
        { action: "loadArticles", category: categoryToLoad, startDate: startDateToLoad, endDate: endDateToLoad },
        showLoadedArticles
    );
}

function getHtmlArticleFromJson(article) {
    console.log(article);
    let htmlArticle = $('<article></article>')
        .addClass('news-article');

    let titleDiv = $('<div></div>')
        .addClass('news-article-title')
        .append(article.articleTitle);
    htmlArticle.append(titleDiv);

    let authorDiv = $('<div></div>')
        .addClass('news-article-author')
        .append(article.author);
    htmlArticle.append(authorDiv);

    let textDiv = $('<div></div>')
        .addClass('news-article-text')
        .append(article.articleText);
    htmlArticle.append(textDiv);

    let dateSpan = $('<span></span>')
        .addClass('news-article-date')
        .append(article.articleDate);
    let categorySpan = $('<span></span>')
        .addClass('news-article-category')
        .append(article.category);

    let footerDiv = $('<div></div>')
        .addClass('news-article-footer')
        .append(dateSpan)
        .append(" | ")
        .append(categorySpan);
    htmlArticle.append(footerDiv);

    let deleteButton = $('<button></button>')
        .addClass('delete-article-button')
        .css("display", "none")
        .html("Delete");
    deleteButton.on('click', () => handleDelete(article.articleId));
    htmlArticle.append(deleteButton);

    let updateButton = $('<form></form>')
        .addClass('update-article-button')
        .attr("action", "update_article.php")
        .attr("method", "POST")
        .css("display", "none")
        .append($("<input></input>").attr("type", "submit").val("Update"))
        .append($("<input></input>").attr("type", "hidden").attr("name", "articleId").attr("id", "articleId").val(article.articleId));
    // updateButton.on('click', () => goToUpdate(article.articleId));
    htmlArticle.append(updateButton);

    return htmlArticle;
}

function showLoadedArticles(allArticles) {
    $("#all-articles").empty();
    allArticles.forEach(article => {
        const htmlArticle = getHtmlArticleFromJson(article);
        $("#all-articles").append(htmlArticle);
    });

    showDeleteUpdateButtonsIfAdmin();
}

function showDeleteUpdateButtonsIfAdmin() {
    $.getJSON(
        "controller/controller.php",
        { action: "getMyNameAndAdminStatus" },
        function (nameAndAdminStatus) {
            if (nameAndAdminStatus['adminStatus'] == 1) {
                $(".delete-article-button").css('display', 'inline-block');
                $(".update-article-button").css('display', 'inline-block');
            }
        }
    );
}

function handleDelete(articleId) {
    if (confirm('Are you sure you want to delete this article?')) {
        $.post(
            'controller/controller.php',
            { action: 'deleteArticle', articleId: articleId },
            function () { console.log('will load'); loadArticlesBasedOnInputs(); },
            'json'
        )
    }
}

function validateDate() {
    if ($(this).val() < "1000-01-01")
        $(this).val("1000-01-01");
    if ($(this).val() > "2500-12-12")
        $(this).val("2500-12-12");
}