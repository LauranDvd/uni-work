let lastCheckDate = new Date(Date.now() + 3 * (60 * 60 * 1000)).toISOString().slice(0, 19).replace('T', ' ');

function getArticles(journalName, callbackFunction) {
    console.log("in getArticles with journalName:", journalName);
    $.getJSON(
        "ArticlesController",
        {action: "getArticles", journalName: journalName},
        callbackFunction
    );
}

function addArticlesInNotification(articles) {
    let notificationTable = $("#notification-div");
    notificationTable.html("<tr style='background-color: mediumseagreen'>\n" +
        "        <td>User</td>\n" +
        "        <td>Journal</td>\n" +
        "        <td>Summary</td>\n" +
        "        <td>Date</td>\n" +
        "    </tr>");

    articles.forEach(function (oneArticle) {
        let row = $("<tr></tr>");
        row.append("<td>" + oneArticle.user + "</td>" +
            "<td>" + oneArticle.journal + "</td>" +
            "<td>" + oneArticle.summary + "</td>" +
            "<td>" + oneArticle.date + "</td>");
        notificationTable.append(row);
    });
}

function notifyAboutNewArticles() {
    $.getJSON(
        "ArticlesController",
        {action: "getAllArticlesSince", date: lastCheckDate},
        function (articles) {
            console.log('New articles since ' + lastCheckDate + ':', articles);
            addArticlesInNotification(articles);
            lastCheckDate = new Date(Date.now() + 3 * (60 * 60 * 1000)).toISOString().slice(0, 19).replace('T', ' ');

        }
    );
}

$(document).ready(function () {
    $("#getArticles").click(function () {
        console.log('you clicked getArticles!');

        let journalName = $("#journalName").val();
        console.log('journalName:', journalName);

        getArticles(journalName, function (articles) {
            console.log('articles:', articles);

            let articlesTable = $("#articlesTable");
            articlesTable.html("");
            articlesTable.append("<tr style='background-color: mediumseagreen'><td>User</td><td>Journal</td>" +
                "<td>Summary</td><td>Date</td></tr>");

            articles.forEach(function (oneArticle) {
                let row = $("<tr></tr>");
                row.append("<td>" + oneArticle.user + "</td>" +
                    "<td>" + oneArticle.journal + "</td>" +
                    "<td>" + oneArticle.summary + "</td>" +
                    "<td>" + oneArticle.date + "</td>");
                articlesTable.append(row);
            });
        });
    });

    $("#logoutButton").click(function () {
        $.post(
            "LogoutController",
            function (response) {
                if (response !== "") {
                    alert('Server error: ' + response);
                }
            },
            'json'
        );
        window.location.href = "./";
    });

    $("#articleForm").submit(function (event) {
        event.preventDefault();

        var formData = $(this).serialize();
        $.post("ArticlesController", formData, function (response) {
            alert('Added the article.');
        }, "json");
    });

    setInterval(notifyAboutNewArticles, 3000);
});
