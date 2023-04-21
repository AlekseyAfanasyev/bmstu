class Ajax {
    post(url, callback) {
        let xhr = new XMLHttpRequest()
<<<<<<< HEAD
        xhr.open('POST', getUrl(url))
=======
        console.log(url)
        xhr.open('POST', url)
>>>>>>> 78095dc1dc3b0c996e56755137eac7d63841119d
        xhr.send()

        xhr.onreadystatechange = () => {
            if (xhr.readyState === 4) {
                const data = JSON.parse(xhr.response)
                callback(data)
            }
        }
    }
}

export const ajax = new Ajax();