$(document).ready(function () {
    populateAboutMeSection();

    populateInputsWithCurrentValues();

    $("#update-article-submit-button").on('click', function () {
        let inputValidationErrors = validateInputs();
        if (inputValidationErrors !== "") {
            alert("Invalid data: " + inputValidationErrors);
            return;
        }

        $.post(
            "controller/controller.php",
            {
                action: "updateArticle",
                id: $("#id-input").val(),
                title: $("#title-input").val(),
                text: $("#text-input").val(),
                author: $("#author-input").val(),
                category: $("#category-input").val(),
                date: $("#date-input").val()
            },
            function (response) {
                if (response != "") {
                    alert('Server error: ' + response);
                }
            },
            'json'
        );
    })
});

function populateAboutMeSection() {
    $.getJSON(
        "controller/controller.php",
        { action: "getMyNameAndAdminStatus" },
        function (nameAndAdminStatus) {
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

function populateInputsWithCurrentValues() {
    $.getJSON(
        "controller/controller.php",
        { action: "getArticleById", articleId: $("#id-input").val() },
        function (article) {
            if (article != null) {
                $("#title-input").val(article.articleTitle);
                $("#text-input").val(article.articleText);
                $("#author-input").val(article.author);
                $("#category-input").val(article.category);
                $("#date-input").val(article.articleDate);
            } else {
                alert('You are looking for an article which does not exist');
            }
        }
    )
}

function validateInputs() {
    let errors = "";

    if ($("#title-input").val() == "")
        errors = errors.concat("title is empty; ");
    if ($("#text-input").val().length < 3)
        errors = errors.concat("text should have at least 3 characters; ");
    if ($("#author-input").val() == "")
        errors = errors.concat("author is empty; ");
    if ($("#category-input").val() == "")
        errors = errors.concat("category is empty; ");
    if ($("#date-input").val() < "1000-01-01")
        errors = errors.concat("date is too early; ");
    if ($("#date-input").val() > "2500-12-12")
        errors = errors.concat("date is too late; ");

    return errors;
}