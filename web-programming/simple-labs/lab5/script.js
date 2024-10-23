"use strict";

const searchInput = document.querySelector("#search-input");
const addButton = document.querySelector("#add-new-option-button");
const combobox = document.querySelector("#countries-select");

const isPreffix = (small, large) => {
    if (small.length > large.length)
        return false;
    return small.toLowerCase() === large.slice(0, small.length).toLowerCase();
}

const updateOptionsBasedOnSearchText = () => {
    const currentText = searchInput.value;

    let countMatching = 0;
    for (let option of combobox.children) {
        if (option.id === "options-count")
            continue;

        let optionValue = option.value;

        if (isPreffix(currentText, optionValue)) {
            if (option.hasAttribute("hidden"))
                option.removeAttribute("hidden");
            countMatching++;
        }
        else
            option.setAttribute("hidden", true);
    }
    document.querySelector("#options-count").innerHTML = `${countMatching} options matching your search`;
    combobox.value = "options-count";
}

const handleAddClick = () => {
    const newOption = document.createElement("option");
    newOption.value = newOption.innerHTML = document.querySelector("#search-input").value;

    combobox.appendChild(newOption);

    updateOptionsBasedOnSearchText();
}

const handleComboboxDoubleClick = () => {
    searchInput.focus();
}

window.onload = () => {
    searchInput.addEventListener("input", updateOptionsBasedOnSearchText);
    addButton.addEventListener("click", handleAddClick);
    combobox.addEventListener("dblclick", handleComboboxDoubleClick);
}
