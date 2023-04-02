import {MainPage} from "./pages/main/index.js";
import {urls} from "./urls.js";

console.log(urls.getGroupMembers())
console.log(1)

const root = document.getElementById('root');

const mainPage = new MainPage(root);
mainPage.render();