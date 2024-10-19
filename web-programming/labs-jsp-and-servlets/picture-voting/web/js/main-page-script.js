const basePicturesUrl = "http:\\\\localhost\\\\facultate\\\\web\\\\pics_app_images\\\\";

function getPics(noPicsToLoad, callbackFunction) {
    $.getJSON(
        "PicturesController",
        {action: "getPics", noPicsToLoad: noPicsToLoad},
        callbackFunction
    );
}

function getMyVote(pictureId, callback) {
    console.log('getting ur vote for ' + pictureId);

    $.getJSON(
        "PicturesController",
        {action: "getMyVote", pictureId: pictureId},
        function (response) {
            console.log('ur vote response: ' + JSON.stringify(response));
            callback(response);
        }
    );
}

function sendVote(pictureId) {
    let voteValue = $("#vote-input-" + pictureId).val();

    console.log('will send vote for ' + pictureId + ' the score is: ' + voteValue);

    $.post(
        "PicturesController",
        {
            action: "votePicture",
            pictureId: pictureId,
            score: voteValue
        },
        function (response) {
            if (response !== "") {
                alert('Server error: ' + response);
            }
        },
        'json'
    );
}

$(document).ready(function () {
    $("#loadPics").click(function () {
        let noPicsToLoad = $("#noPicsToLoad").val();
        getPics(noPicsToLoad, function (pictures) {
            console.log('callback of getpics');

            let picturesTable = $("#picturesTable");
            picturesTable.html("");
            picturesTable.append("<tr style='background-color: mediumseagreen'><td>Uploader</td><td>Photo</td>" +
                "<td>Total score</td><td>Your vote</td></tr>");

            for (const onePic in pictures) {
                let row = $("<tr></tr>");

                row.append("<td>" + pictures[onePic].uploader + "</td>" +
                    "<td><img src='" + basePicturesUrl + pictures[onePic].url + "' width='20%'></td>" +
                    "<td>" + pictures[onePic].totalScore + "</td>");

                picturesTable.append(row);
                getMyVote(pictures[onePic].pictureId, function (myVote) {
                    if (pictures[onePic].uploaderId === parseInt(sessionStorage.getItem("userId"))) {
                        row.append("<td>Your item</td>");
                    } else if (myVote === -1) {
                        row.append(
                            "<td><input type='number' min='1' max='10' id='vote-input-" + pictures[onePic].pictureId + "'>" +
                            "<button onclick='sendVote(" + pictures[onePic].pictureId + ")'>Vote</button>" +
                            "</td>"
                        );
                    } else {
                        row.append("<td>You voted " + myVote + "</td>");
                    }
                });
            }
        })
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
    })
})