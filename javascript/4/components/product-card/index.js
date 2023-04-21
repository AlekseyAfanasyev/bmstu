export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(data) {
        return (
            `
                <div class="card" style="width: 300px;">
<<<<<<< HEAD
                    <img style="opacity: 1" class="accordion-collapse collapse show" id ="picture-${data.id}" src="${data.src}" alt="картинка">
                    <div class="card-body ">
                        <h5 class="card-title">${data.title}</h5>
                        <p class="card-text">${data.text}</p>
                        <button class="btn btn-primary" id="click-card-${data.id}" data-id="${data.id}">Show a sushi cat!</button>
                        <button class="accordeon-button btn btn-primary" id="test-card-${data.id}" data-id="${data.id}" data-bs-toggle="collapse" data-bs-target="#picture-${data.id}"> Collapse a cat</button>
=======
                    <img class="card-img-top" src="${data.photo_400_orig}" alt="картинка">
                    <div class="card-body">
                        <h5 class="card-title">${data.first_name} ${data.last_name}</h5>
                        <button class="btn btn-primary" id="click-card-${data.id}" data-id="${data.id}">Нажми на меня</button>
>>>>>>> 78095dc1dc3b0c996e56755137eac7d63841119d
                    </div>
                </div>
            `
        )
    }
    
    addListeners(data, listener) {
        document.getElementById(`click-card-${data.id}`)
            .addEventListener("click", listener)
<<<<<<< HEAD
        document.getElementById(`test-card-${data.id}`)
=======
        document.getElementById(`click-card-${data.id}`)
>>>>>>> 78095dc1dc3b0c996e56755137eac7d63841119d
             .addEventListener("click", listener)
    }
    
    render(data, listener) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)
    }
}