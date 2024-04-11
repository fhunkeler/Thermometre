function sendData(data) {
  fetch("/api/config", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(data),
  });
}

function handleSubmits(e) {
  e.preventDefault();
  const form = e.target;
  const formData = new FormData(form);

  const data = Object.entries(Object.fromEntries(formData)).reduce((acc, [key, value]) => {
    if (key !== "tabs") {
      const keys = key.split(".");
      if (keys.length === 1) {
        acc[key] = value;
      } else {
        let obj = acc;
        for (let i = 0; i < keys.length - 1; i++) {
          if (!obj[keys[i]]) {
            obj[keys[i]] = {};
          }
          obj = obj[keys[i]];
        }
        obj[keys[keys.length - 1]] = value;
      }
    }
    return acc;
  }, {});
  sendData(data);
}

const form = document.querySelector("#config");
form.addEventListener("submit", handleSubmits);
