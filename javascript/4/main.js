import {MainPage} from "./pages/main/index.js";
<<<<<<< HEAD
import {urls} from "./urls.js";
=======
import {urls} from "./modules/urls.js";
>>>>>>> 78095dc1dc3b0c996e56755137eac7d63841119d

console.log(urls.getGroupMembers())
console.log(1)

const root = document.getElementById('root');

const mainPage = new MainPage(root);
mainPage.render();