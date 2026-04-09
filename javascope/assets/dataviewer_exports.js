window.dash_clientside = Object.assign({}, window.dash_clientside, {
  dataviewer: {
    save_export: async function (payload) {
      if (!payload) {
        return window.dash_clientside.no_update;
      }

      const files = Array.isArray(payload.files) ? payload.files : [payload];

      for (const filePayload of files) {
        const blob = new Blob([filePayload.content], {
          type: filePayload.mime_type || "text/csv",
        });

        if (window.showSaveFilePicker) {
          try {
            const handle = await window.showSaveFilePicker({
              suggestedName: filePayload.filename || "export.csv",
              types: [
                {
                  description: "CSV files",
                  accept: { "text/csv": [".csv"] },
                },
              ],
            });
            const writable = await handle.createWritable();
            await writable.write(blob);
            await writable.close();
            continue;
          } catch (error) {
            if (error && error.name === "AbortError") {
              return window.dash_clientside.no_update;
            }
            alert("Could not save file: " + error);
            return window.dash_clientside.no_update;
          }
        }

        const url = URL.createObjectURL(blob);
        const anchor = document.createElement("a");
        anchor.href = url;
        anchor.download = filePayload.filename || "export.csv";
        document.body.appendChild(anchor);
        anchor.click();
        anchor.remove();
        setTimeout(function () {
          URL.revokeObjectURL(url);
        }, 0);
      }

      return window.dash_clientside.no_update;
    },
  },
});
