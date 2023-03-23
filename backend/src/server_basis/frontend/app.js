const messageInput = document.getElementById('messageInput');
const submitButton = document.getElementById('submitButton');
const messagesContainer = document.getElementById('messages');

// Connect to the WebSocket server
const socket = new WebSocket('ws://107.131.124.5:8000');

// Listen for messages from the server
socket.addEventListener('message', (event) => {
    const messages = JSON.parse(event.data);
    messagesContainer.innerHTML = '';

    messages.forEach((message) => {
        const messageElement = document.createElement('div');
        messageElement.classList.add('message');
        messageElement.textContent = message;
        messagesContainer.appendChild(messageElement);
    });
});

// Send a new message to the server when the submit button is clicked
submitButton.addEventListener('click', () => {
    const message = messageInput.value.trim();
    if (message !== '') {
        socket.send(message);
        messageInput.value = '';
    }
});

