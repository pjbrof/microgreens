FROM node:alpine

COPY ./package.json

RUN npm install

RUN npm run build

COPY . .

CMD ["node", "./src/index.js"]

